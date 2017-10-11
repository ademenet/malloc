/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/11 11:34:54 by ademenet         ###   ########.fr       */
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
** Main free function not thread safe (NTS).
*/

void			free_nts(void *ptr)
{
	t_block		*tmp;

	if (!ptr)
		return ;
	/* que faire si j'ai pas de header ? */
	tmp = (void *)ptr - HEADER_SIZE;
	tmp->free = 1;
	if (tmp->size > SMALL_LIM)
		free_large(tmp);
	// coalesce(tmp);
	// getchar();
}
