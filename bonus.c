/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 10:30:40 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/11 10:37:17 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

	debug("--- Enter coalesce");
	display_list_of_blocks(g_bin.tiny);
	type = which_type(ptr->size);
	if (ptr->next && ptr->next->free && belong_to_zone(ptr, type,
		ptr->next, NULL))
	{
		ptr->next = ptr->next->next;
		if (ptr->next)
		{
			ptr->size = ALIGN(ptr->size + HEADER_SIZE, TINY_RES) + \
				ALIGN(ptr->next->size + HEADER_SIZE, TINY_RES) - HEADER_SIZE;
			ptr->next->size = 0;
			ptr->next->free = 0;
			if (ptr->next->next)
				ptr->next->next->prev = ptr;
		}
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
	debug("--- End coalesce");
	display_list_of_blocks(g_bin.tiny);
	return ;
}

