/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:53:35 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/13 18:22:08 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/* TODO
-putnbr
-putnbrhex
-ft_putstr
*/

void			ft_putstr(char *str)
{
	int			i;
	char		*ptr;

	ptr = str;
	i = 0;
	while(ptr && *ptr && i++)
		++ptr;
	write(1, s, i);
	return ;
}

void			ft_putnbr(size_t nb, int base)
{
	static char	*convert = "0123456789ABCDEF";
	int			converted[64];
	size_t		i;
	size_t		nb_cp;

	i = 0;
	nb_cp = nb;
	while (nb_cp > 0)
	{
		converted[i++] = nb_cp % base;
		nb_cp /= base;
	}
	while (i >= 0)
		write(1, convert[converted[i--]], 1);
	return ;
}

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
	// size_t			true_size;

	tmp = list;
	if (list == g_bin.tiny)
		type = TINY;
	else if (list == g_bin.small)
		type = SMALL;
	else
		type = LARGE;
	while(tmp)
	{
		// fprintf(stderr, "[ ");
		if (tmp->free == 1)
			fprintf(stderr, "%s%12p <| %p  -- %zu -- %p -- %10zu -- = %10zu | free %d |> %-12p%s\n",\
					GRN, (void *)tmp->prev, (void *)tmp, HEADER_SIZE, (void *)tmp + HEADER_SIZE, tmp->size, (tmp->size + HEADER_SIZE), tmp->free, (void *)tmp->next, END);
		else if (tmp->free == 0)
			fprintf(stderr, "%s%12p <| %p  -- %zu -- %p -- %10zu -- = %10zu | free %d |> %-12p%s\n",\
					RED, (void *)tmp->prev, (void *)tmp, HEADER_SIZE, (void *)tmp + HEADER_SIZE, tmp->size, (tmp->size + HEADER_SIZE), tmp->free, (void *)tmp->next, END);
		// true_size = (type == TINY) ? ALIGN((tmp->size + HEADER_SIZE), TINY_RES) : ALIGN((tmp->size + HEADER_SIZE), SMALL_RES);
		// fprintf(stderr, " ] %-10zu\n", true_size);
		tmp = tmp->next;
	}
}
