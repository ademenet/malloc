/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:13 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/09 18:42:57 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/* Avec nouvelle fonction which type : refactoriser + refacto malloc */

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
TODO
- next and prev
	- next && prev
	- next == NULL && prev
	- next && prev == NULL
- detect if i'm on a zone border
- detect free zone and munmap them
*/

static int		belong_to_zone(t_block *cur, t_block *next, t_block *prev)
{
	void		*tiny;
	void		*small;
	t_type		type;

	type = which_type();
	if (next)
	{
		tiny = (void *)cur + ALIGN((HEADER_SIZE + cur->size), TINY_RES);
		tiny = (void *)prev + ALIGN((HEADER_SIZE + prev->size), TINY_RES);
		debug("next: tiny %p =? next %p", tiny, next);
		debug("next: small %p =? next %p", small, next);
		if (tiny == next)
		return (1);
		if (small == next)
		return (1);
	}
	else if (prev)
	{
		small = (void *)prev + ALIGN((HEADER_SIZE + prev->size), SMALL_RES);
		small = (void *)cur + ALIGN((HEADER_SIZE + cur->size), SMALL_RES);
		debug("prev: tiny %p =? cur %p", tiny, cur);
		debug("prev: small %p =? cur %p", small, cur);
		if (tiny == cur)
			return (1);
		if (small == cur)
			return (1);
	}
	return (0);
}

/* PROB: je ne sais pas quel arrondi faire */

void			coalesce(t_block *ptr)
{
	size_t		new_size;

	if (ptr->next && ptr->next->free && belong_to_zone(ptr, ptr->next, NULL))
	{
		ptr->next = ptr->next->next;
		ptr->size = ptr->size + ALIGN(ptr->next->size + HEADER_SIZE, TINY_RES);
		ptr->next->size = 0;
		ptr->next->free = 0;
		if (ptr->next->next)
			ptr->next->next->prev = ptr;
	}
	if (ptr->prev && ptr->prev->free && belong_to_zone(ptr, NULL, ptr->prev))
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size = ptr->prev->size + ALIGN(ptr->size + HEADER_SIZE, TINY_RES);
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
	debug("--- tmp a free == %p", tmp);
	if (tmp->size > SMALL_LIM)
		free_large(tmp);
	coalesce(tmp);
}
