/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:53:35 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/11 11:33:36 by ademenet         ###   ########.fr       */
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
	t_type		type;
	size_t			true_size;

	tmp = list;
	if (list == g_bin.tiny)
		type = TINY;
	else if (list == g_bin.small)
		type = SMALL;
	else
		type = LARGE;
	while(tmp)
	{
		fprintf(stderr, "[ ");
		if (tmp->free == 1)
			fprintf(stderr, "%s%12p <| prev | cur %p | size %10zu | free %d | next |> %-12p%s",\
					GRN, (void *)tmp->prev, (void*)tmp, tmp->size, tmp->free, (void *)tmp->next, END);
		else if (tmp->free == 0)
			fprintf(stderr, "%s%12p <| prev | cur %p | size %10zu | free %d | next |> %-12p%s",\
				RED, (void *)tmp->prev, (void*)tmp, tmp->size, tmp->free, (void *)tmp->next, END);
		true_size = (type == TINY) ? ALIGN((tmp->size + HEADER_SIZE), TINY_RES) : ALIGN((tmp->size + HEADER_SIZE), SMALL_RES);
		fprintf(stderr, " ] %-10zu\n", true_size);
		tmp = tmp->next;
	}
}
