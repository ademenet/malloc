/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:13:50 by ademenet          #+#    #+#             */
/*   Updated: 2017/09/28 19:15:10 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This is our main global maintaining bins: tiny, small and large.
*/

t_bin			g_bin = {NULL, NULL, NULL}

/*
** Main free function not thread safe (NTS).
*/

void			free_nts(void *ptr)
{
	if (ptr == 0)
		return;
	// Idee : mettre un flag pour reconnaitre si vraiment memoire alloue
	// mettre le pointeur sur libre
	
}

/*
** Main malloc function not thread safe (NTS).
** Returns a point to the payload (rounded to resolution of type) of a memory
** block.
*/

void			*malloc_nts(size_t size)
{
	t_block		*new;

	if (!g_bin->tiny)
		g_bin->tiny = mmap(0, TINY_SIZE, PROT_SET, MAP_SET, -1, 0);
	if (!g_bin->small)
		g_bin->small = mmap(0, SMALL_SIZE, PROT_SET, MAP_SET, -1, 0);
	new = allocate(size);
	new->free = 0
	// if (size == 0)
	// 	return (NULL);
	// if (size <= TINY_LIM)
	// 	new = allocate(size, TINY);
	// if (size <= SMALL_LIM)
	// 	new = allocate(size, SMALL)
	// if (size > SMALL_BORDER)
	// 	new = allocate_large(size, LARGE);
	// return(&(*new) + HEADER_SIZE);
	return ((void*)new + HEADER_SIZE);
}

/*
** 
*/

// ALIGN((size + HEADER_SIZE), TINY_RES)

	// if (!g_bin->tiny)
	// {
	// 	g_bin->tiny = mmap(0, TINY_SIZE, PROT_SET, MAP_SET, -1, 0);
	// }
	// else if (!g_bin->small)
	// {
	// 	g_bin->tiny = mmap(0, SMALL_SIZE, PROT_SET, MAP_SET, -1, 0);
	// }
	// else if (!g_bin->large)
	// 	allocate_large(size);


void			allocate(size_t size, t_block *list, t_type type)
{
	t_ui		true_size;
	t_block		new_block;

	if (type == TINY)
		true_size = ALIGN((size + HEADER_SIZE), TINY_RES);
	else if (type == SMALL)
		true_size = ALIGN((size + HEADER_SIZE), SMALL_RES);
	else if (type == LARGE)
		true_size = ALIGN((size + HEADER_SIZE), getpagesize());		
	while (list->next)
	{
		if (list->free == 1 && true_size <= list->size)
			new_block = list;
	}
	new_block->size = size;
	return ;
}

// prend une taille et retourne un pointeur sur l'adresse
void			*allocate_large(size_t size)
{
	t_block		*new_large;

	// printf("block_size : %d", block_size);
	new_large = mmap(0, ALIGN((size + HEADER_SIZE), getpagesize()), PROT_SET, 
					   MAP_SET, -1, 0);
	new_large->size = ALIGN((size + HEADER_SIZE), getpagesize())
	new_large->free = 0;
	return (new_large);
}

/*
** Main realloc function not thread safe (NTS).
** Requests to resize payload region pointed to by ptr to size.
*/

void			*realloc_nts(void *ptr, size_t size)
{
	return(NULL);
}
