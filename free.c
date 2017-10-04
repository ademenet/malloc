/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/04 18:02:07 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
TODO
- next and prev
- detect if i'm on a zone border
- detect free zone and munmap them
*/

void			coalesce_next(t_block *ptr)
{
	if (ptr->next->free == 1)
	{
		ptr->next = ptr->next->next;
		ptr->next->next = NULL;
		ptr->size = ptr->size + ptr->next->size + HEADER_SIZE;
		ptr->next->size = 0;
		ptr->next->free = 0;
	}
	if (ptr->prev->free == 1)
	{
		
	}
	return ;
}

/*
** Main free function not thread safe (NTS).
*/

void			free_nts(void *ptr)
{
	t_block		*tmp;

	if (ptr == 0)
		return ;
	tmp = (void*)ptr - HEADER_SIZE;
	tmp->free = 1;
	// Idee : mettre un flag pour reconnaitre si vraiment memoire alloue
	// mettre le pointeur sur libre
	
}
