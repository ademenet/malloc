/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:41:46 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/17 19:44:38 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	display_block(void *start, void *end, int size)
{
	ft_putstr("0x");
	ft_putnbrbase((size_t)start, 16);
	ft_putstr(" - 0x");
	ft_putnbrbase((size_t)end, 16);
	ft_putstr(" : ");
	ft_putnbrbase(size, 10);
	ft_putstr(" octets\n");
	return ;
}

static void	display_block_colour(int free, void *start, void *end, int size)
{
	if (free == 1)
	{
		ft_putstr("\033[32;m");
		display_block(start, end, size);
		ft_putstr("\033[0m");
	}
	else if (free == 0)
	{
		ft_putstr("\033[31;m");
		display_block(start, end, size);
		ft_putstr("\033[0m");
	}
	return ;
}

static int	display_list(t_block *list, int show_all)
{
	t_block	*tmp;
	void	*start;
	void	*end;
	int		subtotal;

	tmp = list;
	subtotal = 0;
	while (tmp)
	{
		if (tmp->free == 0 || show_all)
		{
			start = (void*)tmp + HEADER_SIZE;
			end = (void*)tmp + (HEADER_SIZE + tmp->size);
			subtotal += tmp->size;
			if (show_all)
				display_block_colour(tmp->free, start, end, tmp->size);
			else
				display_block(start, end, tmp->size);
		}
		tmp = tmp->next;
	}
	return (subtotal);
}

void		show_alloc_mem_all(void)
{
	int		total;

	total = 0;
	ft_putstr("TINY : 0x");
	ft_putnbrbase((size_t)g_bin.tiny, 16);
	ft_putstr("\n");
	total += display_list(g_bin.tiny, 1);
	ft_putstr("SMALL : 0x");
	ft_putnbrbase((size_t)g_bin.small, 16);
	ft_putstr("\n");
	total += display_list(g_bin.small, 1);
	ft_putstr("LARGE : 0x");
	ft_putnbrbase((size_t)g_bin.large, 16);
	ft_putstr("\n");
	total += display_list(g_bin.large, 1);
	ft_putstr("Total : ");
	ft_putnbrbase((size_t)total, 10);
	ft_putstr(" octets\n");
	return ;
}

void		show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	ft_putstr("TINY : 0x");
	ft_putnbrbase((size_t)g_bin.tiny, 16);
	ft_putstr("\n");
	total += display_list(g_bin.tiny, 0);
	ft_putstr("SMALL : 0x");
	ft_putnbrbase((size_t)g_bin.small, 16);
	ft_putstr("\n");
	total += display_list(g_bin.small, 0);
	ft_putstr("LARGE : 0x");
	ft_putnbrbase((size_t)g_bin.large, 16);
	ft_putstr("\n");
	total += display_list(g_bin.large, 0);
	ft_putstr("Total : ");
	ft_putnbrbase((size_t)total, 10);
	ft_putstr(" octets\n");
	return ;
}
