/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:09:30 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/18 13:56:06 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_fastmutex = PTHREAD_MUTEX_INITIALIZER;

/*
** Initiates malloc's tiny and small pages.
*/

void			init_malloc(void)
{
	t_block		*init;

	if (!g_bin.tiny)
	{
		init = mmap(0, TINY_ZONE, PROT_SET, MAP_SET, -1, 0);
		init->size = TINY_ZONE - HEADER_SIZE;
		init->free = 1;
		init->prev = NULL;
		init->next = NULL;
		g_bin.tiny = init;
	}
	if (!g_bin.small)
	{
		init = mmap(0, SMALL_ZONE, PROT_SET, MAP_SET, -1, 0);
		init->size = SMALL_ZONE - HEADER_SIZE;
		init->free = 1;
		init->prev = NULL;
		init->next = NULL;
		g_bin.small = init;
	}
	return ;
}

void			*malloc(size_t size)
{
	void		*ptr;

	pthread_mutex_lock(&g_fastmutex);
	ptr = malloc_nts(size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_fastmutex);
	free_nts(ptr);
	pthread_mutex_unlock(&g_fastmutex);
}

void			*realloc(void *ptr, size_t size)
{
	void		*ptr_ts;

	pthread_mutex_lock(&g_fastmutex);
	ptr_ts = realloc_nts(ptr, size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr_ts);
}
