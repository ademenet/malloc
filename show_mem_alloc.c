/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:41:46 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/10 14:54:52 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	display_list(t_block *list, int show_all)
{
	t_block	*tmp;
	void	*start;
	void	*end;
	int 	subtotal;

	tmp = list;
	subtotal = 0;
	while (tmp)
	{
		if (tmp->free == 0 || show_all)
		{
			start = (void*)tmp + HEADER_SIZE;
			end = (void*)tmp + (HEADER_SIZE + tmp->size);
			subtotal += tmp->size;
			if (show_all && tmp->free == 1)
				printf("\033[32;m%p - %p : %zu octets\033[0m\n" END, start, end, tmp->size);
			else if (show_all && tmp->free == 0)
				printf("\033[31;m%p - %p : %zu octets\033[0m\n", start, end, tmp->size);
			else	
				printf("%p - %p : %zu octets\n", start, end, tmp->size);			
		}
		tmp = tmp->next;
	}
	return (subtotal);
}

void		show_mem_alloc_all(void)
{
	t_block	*tmp;
	int		total;

	total = 0;
	printf("TINY : %p\n", g_bin.tiny);
	total += display_list(g_bin.tiny, 1);
	printf("SMALL : %p\n", g_bin.small);
	total += display_list(g_bin.small, 1);
	printf("LARGE : %p\n", g_bin.large);
	total += display_list(g_bin.large, 1);
	printf("Total : %d octets\n", total);
	return ;	
}

void		show_mem_alloc(void)
{
	t_block	*tmp;
	int		total;

	total = 0;
	printf("TINY : %p\n", g_bin.tiny);
	total += display_list(g_bin.tiny, 0);
	printf("SMALL : %p\n", g_bin.small);
	total += display_list(g_bin.small, 0);
	printf("LARGE : %p\n", g_bin.large);
	total += display_list(g_bin.large, 0);
	printf("Total : %d octets\n", total);
	/* Passer pas en int */
	return ;
}
