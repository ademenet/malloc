/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:13:50 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/11 16:55:50 by ademenet         ###   ########.fr       */
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

	new_large = mmap(0, ALIGN((size + HEADER_SIZE), getpagesize()), PROT_SET, \
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
** that fits the best to our demand: size + our header. Returns the beginning of
** the block aka the header.
*/

static void		*find_fit(t_block *list, size_t size)
{
	t_block		*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->free == 1 && size <= tmp->size)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** Extends the heap by calling one more time mmap() function. This new zone is
** linked to the old one in the same linked list.
*/

static t_block	*extend_heap(t_block *list, size_t size, t_type type)
{
	t_block		*new_block;
	t_block		*next_block;
	t_block		*prev_block;

	new_block = (type == TINY) ? mmap(0, TINY_ZONE, PROT_SET, MAP_SET, -1, 0) :\
		mmap(0, SMALL_ZONE, PROT_SET, MAP_SET, -1, 0);
	new_block->free = 0;
	new_block->size = size;
	prev_block = list;
	while (prev_block->next)
		prev_block = prev_block->next;
	new_block->prev = prev_block;
	prev_block->next = new_block;
	next_block = (void *)new_block + (HEADER_SIZE + size);
	new_block->next = next_block;
	if (type == TINY)
		next_block->size = TINY_ZONE - (HEADER_SIZE + size);
	else if (type == SMALL)
		next_block->size = SMALL_ZONE - (HEADER_SIZE + size);
	next_block->free = 1;
	next_block->prev = new_block;
	next_block->next = NULL;
	return (new_block);
}

/*
** Manages tiny and small allocations by placing headers and returning the
** available space afterwards.
*/

static t_block	*allocate(size_t size, t_block *list, t_type type)
{
	t_block		*new_block;
	t_block		*next_block;

	if ((new_block = find_fit(list, size)) != NULL)
	{
		next_block = (void *)new_block + (HEADER_SIZE + size);
		if ((new_block->size - (HEADER_SIZE + size)) > (HEADER_SIZE + 1) && \
			(HEADER_SIZE + size) <= new_block->size && \
			(void *)next_block != (void *)new_block->next)
		{
			next_block->size = new_block->size - (HEADER_SIZE + size);
			next_block->free = 1;
			next_block->prev = new_block;
			next_block->next = new_block->next;
			new_block->next = next_block;
		}
		else
			size += new_block->size - size;
		new_block->size = size;
		new_block->free = 0;
	}
	else
		new_block = extend_heap(list, size, type);
	return (new_block);
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
	if (size == 0)
		size = 1;
	if (size >= SIZE_T_MAX)
		size = SIZE_T_MAX - HEADER_SIZE;
	if (size > 0 && size <= TINY_LIM)
		new = allocate(size, g_bin.tiny, TINY);
	else if (size > TINY_LIM && size <= SMALL_LIM)
		new = allocate(size, g_bin.small, SMALL);
	else
		new = allocate_large(size);
	return ((void*)new + HEADER_SIZE);
}
