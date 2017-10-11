/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 10:30:40 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/11 15:33:38 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** See if the next or previous block belongs to the same zone.
** To do this, check whether the next or prev address is contiguous. If yes 
** returns 1, if no returns 0.
*/

static int		belong_to_zone(t_block *cur, t_block *next, t_block *prev)
{
	void		*to_check;

	if (next)
		to_check = (void *)next - (HEADER_SIZE + cur->size);
	else if (prev)
		to_check = (void *)prev + (HEADER_SIZE + prev->size);
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
	if (ptr->next && ptr->next->free && belong_to_zone(ptr, ptr->next, NULL))
	{
		ptr->size = ptr->size + HEADER_SIZE + ptr->next->size;
		if (ptr->next->next)
			ptr->next->next->prev = ptr;
		ptr->next = ptr->next->next;
	}
	if (ptr->prev && ptr->prev->free && belong_to_zone(ptr, NULL, ptr->prev))
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size = ptr->prev->size + HEADER_SIZE + ptr->size;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
	}
	return ;
}

