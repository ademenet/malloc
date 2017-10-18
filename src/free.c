/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/18 14:01:26 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Clears the large allocated memory and ensures integrity of the large
** allocation list.
*/

static void			free_large(t_block *ptr)
{
	t_block			*tmp;
	int				errno;

	tmp = g_bin.large;
	while (tmp)
	{
		if (tmp == ptr)
			break ;
	}
	if (tmp)
	{
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if ((errno = munmap(ptr, (ALIGN((ptr->size + HEADER_SIZE), \
			getpagesize())))))
			return ;
	}
	return ;
}

/*
** Main free function not thread safe (NTS).
*/

void				free_nts(void *ptr)
{
	t_block			*tmp;

	if (!ptr)
		return ;
	tmp = (void *)ptr - HEADER_SIZE;
	if (check_in_list(tmp))
	{
		tmp->free = 1;
		if (tmp->size > SMALL_LIM)
			free_large(tmp);
		coalesce(tmp);
	}
}
