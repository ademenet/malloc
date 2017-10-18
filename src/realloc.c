/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:36 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/18 16:39:28 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*pdst;
	const char	*psrc;

	pdst = (char *)dst;
	psrc = (const char *)src;
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}

static void		*split_or_merge(t_block *tmp, void *ptr, size_t size)
{
	t_block		*next;
	
	next = NULL;
	if (((tmp->size + HEADER_SIZE + tmp->next->size) - size) >=
	HEADER_SIZE + 1)
	{
		next = (void *)ptr + size;
		next->size = (tmp->size + HEADER_SIZE + tmp->next->size) - size;
		next->free = 1;
		next->next = tmp->next;
		tmp->next->prev = next;
		tmp->next = next;
		next->prev = tmp;
	}
	else
	{
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
		tmp->size = tmp->size + HEADER_SIZE + tmp->next->size;
	}
	return (tmp);
}

static void		*reallocate(t_block *tmp, void *ptr, size_t size, int f_free)
{
	t_block		*new;

	if (tmp->next && tmp->next->free == 1 &&
		(tmp->size + HEADER_SIZE + tmp->next->size >= size))
		return (split_or_merge(tmp, ptr, size));
	else
	{
		new = malloc_nts(size);
		ft_memcpy(new, ptr, tmp->size);
		if (f_free)
			free_nts(ptr);
		return (new);
	}
	return (NULL);
}

void			*reallocf_nts(void *ptr, size_t size)
{
	t_block		*tmp;

	if (ptr == NULL && size > 0)
		return (malloc_nts(size));
	if (ptr != NULL && size == 0)
	{
		if (check_in_list(ptr))
			free(ptr);
		return (malloc_nts(HEADER_SIZE + 1));		
	}
	tmp = (void *)ptr - HEADER_SIZE;
	if (check_in_list(tmp))
		return(reallocate(tmp, ptr, size, 1));
	return (NULL);
}

/*
** Main realloc function not thread safe (NTS).
** Requests to resize payload region pointed to by ptr to size.
*/

void			*realloc_nts(void *ptr, size_t size)
{
	t_block		*tmp;

	if (ptr == NULL && size > 0)
		return (malloc_nts(size));
	if (ptr != NULL && size == 0)
	{
		if (check_in_list(ptr))
			free(ptr);
		return (malloc_nts(HEADER_SIZE + 1));		
	}
	tmp = (void *)ptr - HEADER_SIZE;
	if (check_in_list(tmp))
		return(reallocate(tmp, ptr, size, 0));
	return (NULL);
}

