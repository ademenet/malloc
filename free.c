/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/10 17:06:15 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/* Avec nouvelle fonction which type : refactoriser + refacto malloc */

/*
** Clears the large allocated memory and ensures integrity of the large 
** allocation list.
*/

static void			free_large(t_block *ptr)
{
	t_block		*tmp;
	int			errno;

	tmp = g_bin.large;
	while (tmp)
	{
		if (tmp == ptr)
			break;
	}
	if (tmp)
	{
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if ((errno = munmap(ptr, (ALIGN((ptr->size + HEADER_SIZE), \
			getpagesize())))))
			exit(errno);
	}
	return ;
}

/*
** See if the next or previous block belongs to the same zone.
** To do this, check whether the next or prev address is contiguous. If yes 
** returns 1, if no returns 0.
*/

static int		belong_to_zone(t_block *cur, t_type type, t_block *next,
				t_block *prev)
{
	void		*to_check;

	if (next)
	{
		to_check = (type == TINY) ? \
			(void *)next - ALIGN((HEADER_SIZE + cur->size), TINY_RES) : \
			(void *)next - ALIGN((HEADER_SIZE + cur->size), SMALL_RES);
	}
	else if (prev)
	{
		to_check = (type == TINY) ? \
			(void *)prev + ALIGN((HEADER_SIZE + prev->size), TINY_RES) : \
			(void *)prev + ALIGN((HEADER_SIZE + prev->size), SMALL_RES);
	}
	if (cur == to_check)
		return (1);
	else
		return (0);
}

/*
** Merge adjacent free blocks together: coalesce.
*/

void			coalesce(t_block *ptr)
{
	size_t		new_size;
	t_type		type;

	type = which_type(ptr->size);
	if (ptr->next && ptr->next->free && belong_to_zone(ptr, type,
		ptr->next, NULL))
	{
		ptr->next = ptr->next->next;
		ptr->size = ALIGN(ptr->size + HEADER_SIZE, TINY_RES) + \
			ALIGN(ptr->next->size + HEADER_SIZE, TINY_RES) - HEADER_SIZE;
		ptr->next->size = 0;
		ptr->next->free = 0;
		if (ptr->next->next)
			ptr->next->next->prev = ptr;
	}
	if (ptr->prev && ptr->prev->free && belong_to_zone(ptr, type, NULL,
		ptr->prev))
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size = ALIGN(ptr->prev->size + HEADER_SIZE, TINY_RES) + \
			ALIGN(ptr->size + HEADER_SIZE, TINY_RES) - HEADER_SIZE;
		ptr->size = 0;
		ptr->free = 0;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
	}
	return ;
}

/*
** Main free function not thread safe (NTS).
*/

void			free_nts(void *ptr)
{
	t_block		*tmp;

	if (!ptr)
		return ;
	/* que faire si j'ai pas de header ? */
	tmp = (void*)ptr - HEADER_SIZE;
	tmp->free = 1;
	if (tmp->size > SMALL_LIM)
		free_large(tmp);
	coalesce(tmp);
}
