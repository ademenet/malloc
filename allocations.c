/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:13:50 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/04 16:53:02 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_bin			g_bin = {NULL, NULL, NULL};

/*
** Manages large allocations. It allocates the size rounded to the upper next
** getpagesize() boundary and maintains the list.
*/

static void		*allocate_large(size_t size)
{
	t_block		*new_large;
	t_block		*tmp;

	new_large = mmap(0, ALIGN((size + HEADER_SIZE), getpagesize()), PROT_SET, 
					 MAP_SET, -1, 0);
	new_large->size = size;
	new_large->free = 0;
	if (!g_bin.large)
	{
		g_bin.large = new_large;
		new_large->next = NULL;
		new_large->prev = NULL;
	}
	else
	{
		tmp = g_bin.large;
		while (tmp->next != NULL || new_large < tmp->next)
			tmp = tmp->next;
		new_large->prev = tmp;
		new_large->next = tmp->next;
		tmp->next = new_large;
	}
	return (new_large);
}

/*
** Finds the first fit block. Could be optimized with best fit: find the block
** that fits the best to our demand.
*/

/* TODO mettre la fonction de coalescence dans le parcours de la liste aussi */

static void		*find_fit(t_block *list, size_t true_size)
{
	t_block 	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->free == 1 && true_size <= tmp->size)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** Extends the heap by calling one more time mmap() function. This new zone is
** linked to the old one in the same linked list.
*/

static t_block	*extend_heap(t_block *list, size_t size, size_t true_size,
	t_type type)
{
	t_block		*new_block;
	t_block		*next_block;
	t_block		*prev_block;

	new_block = (type == TINY) ? mmap(0, TINY_ZONE, PROT_SET, MAP_SET, -1, 0) :\
		mmap(0, SMALL_ZONE, PROT_SET, MAP_SET, -1, 0);
	debug("new_block = %p", new_block);
	debug("true_size = %zu", true_size);
	getchar();
	new_block->free = 0;
	new_block->size = size;
	prev_block = list;
	while (prev_block->next)
		prev_block = prev_block->next;
	// debug("prev_block = %p", prev_block);
	// debug("prev_block->next = %p", prev_block->next);
	new_block->prev = prev_block;
	prev_block->next = new_block;
	// debug("prev_block->next = %p", prev_block->next);
	next_block = (void*)new_block + true_size;
	// debug("next_block = %p", next_block);
	new_block->next = next_block;
	// debug("new_block->next = %p", new_block->next);
	if (type == TINY)
		next_block->size = TINY_ZONE - true_size;
	else if (type == SMALL)
		next_block->size = SMALL_ZONE - true_size;
	// debug("next_block->size = %zu", next_block->size);
	next_block->free = 1;
	next_block->prev = new_block;
	// debug("next_block->prev = %p", next_block->prev);
	next_block->next = NULL;
	// getchar();
	return (new_block);
}

/*
** Manages tiny and small allocations by placing headers and returning the
** available space afterwards.
*/

/* TODO Segfault du a un decalage dans la seconde zone : 
mon algo croit quil y a plus de places restantes quil ny en a pour de vrai
peut etre solution : dans linitalisation de la seconde page, je cree un decalage
des le debut.
*/

static t_block	*allocate(size_t size, t_block *list, t_type type)
{
	size_t		true_size;
	t_block		*new_block;
	t_block		*next_block;

	true_size = (type == TINY) ? ALIGN((size + HEADER_SIZE), TINY_RES) : \
		ALIGN((size + HEADER_SIZE), SMALL_RES);
	if ((new_block = find_fit(list, true_size)) != NULL)
	{
		debug("new_block in find_fit : %p", new_block);
		if (((new_block->size + HEADER_SIZE) - true_size) > 0)
		{
			debug("(%zu + %lu) - %zu = %d", new_block->size,HEADER_SIZE,true_size,(new_block->size + HEADER_SIZE) - true_size);
			next_block = (void*)new_block + true_size;
			debug("next_block = %p", next_block);
			debug("next_block->free = %d", next_block->free); 
			next_block->free = 1;
			debug("new_block->size = %zu", new_block->size);
			debug("next_block->size = %zu", next_block->size);
			next_block->size = new_block->size - true_size;
			next_block->prev = new_block;
			next_block->next = new_block->next;
			new_block->next = next_block;
		}
		new_block->size = size;
		new_block->free = 0;
	}
	else
		new_block = extend_heap(list, size, true_size, type);
	debug("new_block : %p", new_block);
	return (new_block);
}

/*
** Initiates malloc's tiny and small pages.
*/

static void		init_malloc(void)
{
	t_block		*init;

	if (!g_bin.tiny)
	{
		init = mmap(0, TINY_ZONE, PROT_SET, MAP_SET, -1, 0);
		init->size = TINY_ZONE - HEADER_SIZE;
		init->free = 1;
		init->prev = NULL;
		init->next = NULL;
		g_bin.tiny = init;
	}
	if (!g_bin.small)
	{
		init = mmap(0, SMALL_ZONE, PROT_SET, MAP_SET, -1, 0);
		init->size = SMALL_ZONE - HEADER_SIZE;
		init->free = 1;
		init->prev = NULL;
		init->next = NULL;
		g_bin.small = init;
	}
	return ;
}

/*
** Main malloc function not thread safe (NTS).
** Returns a pointer to the payload (rounded to resolution of type) of a memory
** block.
*/

void			*malloc_nts(size_t size)
{
	t_block		*new;

	init_malloc();
	if (size <= TINY_LIM)
		new = allocate(size, g_bin.tiny, TINY);
	else if (size <= SMALL_LIM)
		new = allocate(size, g_bin.small, SMALL);
	else
		new = allocate_large(size);
	debug("new = %p", new);
	return ((void*)new + HEADER_SIZE);
}
