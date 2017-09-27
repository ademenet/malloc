/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:13:50 by ademenet          #+#    #+#             */
/*   Updated: 2017/09/27 17:21:17 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	if (ptr == 0)
		return;
}

void		*malloc_(size_t size)
{
	void	*block;

	if (size == 0)
		return (NULL);
	else if (size < TINY_RES)
	{
		size = ALIGN_TINY(size);
	}
	if (size < SMALL_RES)
	{
		size = ALIGN_SMALL(size);
	}
	else if (size < SMALL_SIZE)
	// {
		
	// }
	// else
	// {
		
	// }
	if (size > SMALL_BORDER)
		allocate(size, LARGE);
	return(block);
}

void		allocate(size_t size, t_type type)
{
	if (type == TINY)
		return ;
	else if (type == SMALL)
		return ;
	else if (type == LARGE)
		allocate_large(size);
	return ;
}

// prend une taille et retourne un pointeur sur l'adresse
void		*allocate_large(size_t size)
{
	void	*block_large;
	int		block_size;

	block_size = int((size / get_page_size())) + 1;
	printf("block_size : %d", block_size);
	block_large = mmap(0, size, PROT_READ | PROD_WRITE, MAP_ANON | MAN_PRIVATE,
					   -1, 0);
	return (block_large);
}

void		*realloc(void *ptr, size_t size)
{
	return(NULL);
}
