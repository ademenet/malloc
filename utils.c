/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:53:35 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/09 18:10:31 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Look at which type (TINY, SMALL or LARGE) belongs to the size passed in 
** parameter and returns a t_type of the type in question.
*/

t_type			which_type(size_t size)
{
	if (size > 0 && size <= TINY_LIM)
		return (TINY);
	else if (size > TINY_LIM && size <= SMALL_LIM)
		return (SMALL);
	else
		return (LARGE);
}

void			display_list_of_blocks(t_block *list)
{
    t_block		*tmp;

	tmp = list;
	while(tmp)
	{
		fprintf(stderr, "list->size:\t%zu\nlist->next:\t%p\nlist->free:\t%d\n",\
				  list->size, list->next, list->free);
		fprintf(stderr, "---\n");
		tmp = tmp->next;
	}
}
