/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/06 11:49:13 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
TODO
- next and prev
- detect if i'm on a zone border
- detect free zone and munmap them
*/

void			coalesce(t_block *ptr)
{
	size_t		new_size;

	if (ptr->next && ptr->next->free)
	{
		ptr->next = ptr->next->next;
		ptr->size = ptr->size + ptr->next->size + HEADER_SIZE;
		ptr->next->size = 0;
		ptr->next->free = 0;
		if (ptr->next->next)
			ptr->next->next->prev = ptr;
	}
	if (ptr->prev && ptr->prev->free)
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size = ptr->prev->size + ptr->size + HEADER_SIZE;
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
	coalesce(tmp);	
}
