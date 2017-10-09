/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:00:36 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/09 14:00:26 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Main realloc function not thread safe (NTS).
** Requests to resize payload region pointed to by ptr to size.
*/

void			*realloc_nts(void *ptr, size_t size)
{
	t_block		*tmp;

	tmp = (void *)ptr - HEADER_SIZE;
	if (tmp && tmp->next)
	{
		if (tmp->next->free == 1 && (tmp->size + tmp->next->free + HEADER_SIZE
			>= size))
		{
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
		}
		else
			tmp = malloc_nts(size);
		return (tmp)
	}
	return(NULL);
}
