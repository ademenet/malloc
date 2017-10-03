/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/02 18:37:49 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	return ;
}

/*
** Main free function not thread safe (NTS).
*/

void			free_nts(void *ptr)
{
	t_block		*tmp;

	tmp = ptr - HEADER_SIZE;
	tmp->free = 1;
	if (ptr == 0)
		return;
	// Idee : mettre un flag pour reconnaitre si vraiment memoire alloue
	// mettre le pointeur sur libre
	
}
