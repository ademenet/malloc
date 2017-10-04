/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:53:35 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/04 14:00:14 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
