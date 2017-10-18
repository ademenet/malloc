/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:09:30 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/18 18:24:11 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_fastmutex = PTHREAD_MUTEX_INITIALIZER;

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
	ptr_ts = realloc_nts(ptr, size, 0);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr_ts);
}

void			*reallocf(void *ptr, size_t size)
{
	void		*ptr_ts;

	pthread_mutex_lock(&g_fastmutex);
	ptr_ts = realloc_nts(ptr, size, 1);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr_ts);
}

void			*calloc(size_t count, size_t size)
{
	void		*ptr_ts;

	pthread_mutex_lock(&g_fastmutex);
	ptr_ts = calloc_nts(count, size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr_ts);
}
