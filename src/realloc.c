/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:36 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/11 17:14:04 by ademenet         ###   ########.fr       */
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

/*
** Main realloc function not thread safe (NTS).
** Requests to resize payload region pointed to by ptr to size.
*/

/* The realloc() function tries to change the size of the allocation pointed to by ptr to size, and
     returns ptr.  If there is not enough room to enlarge the memory allocation pointed to by ptr, realloc()
     creates a new allocation, copies as much of the old data pointed to by ptr as will fit to the new allo-
     cation, frees the old allocation, and returns a pointer to the allocated memory.  If ptr is NULL,
     realloc() is identical to a call to malloc() for size bytes.  If size is zero and ptr is not NULL, a
     new, minimum sized object is allocated and the original object is freed.  When extending a region allo-
     cated with calloc(3), realloc(3) does not guarantee that the additional memory is also zero-filled.

     The reallocf() function is identical to the realloc() function, except that it will free the passed
     pointer when the requested memory cannot be allocated.  This is a FreeBSD specific API designed to ease
	 the problems with traditional coding styles for realloc causing memory leaks in libraries.
*/

void			*realloc_nts(void *ptr, size_t size)
{
	t_block		*tmp;
	t_block		*new;

	
	if (ptr == NULL && size > 0)
		return (malloc_nts(size));
	if (ptr != NULL && size == 0)
	{
		/* Pas sur... */
		free(ptr);
		return (malloc_nts(HEADER_SIZE + 1));		
	}
	tmp = (void *)ptr - HEADER_SIZE;
	if (tmp && tmp->next)
	{
		if (tmp->next->free == 1 && (tmp->size + HEADER_SIZE + tmp->next->size
			>= size))
		{
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			tmp->size = tmp->size + HEADER_SIZE + tmp->next->size;
		}
		else
		{
			new = malloc_nts(size);
			ft_memcpy(new, ptr, tmp->size);
			free(ptr);
		}
		return (tmp);
	}
	return (NULL);
}
