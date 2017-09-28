/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:59:43 by ademenet          #+#    #+#             */
/*   Updated: 2017/09/28 18:29:51 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	t_block	block;
	int i;
	for (i = 1; i <= 32; i = i + 1) {
		printf("ALIGN(%d + %lu) = %lu\n", i, HEADER_SIZE, ALIGN((i + HEADER_SIZE), TINY_RES));
		// printf("%s\n", i, typeof(ALIGN(i, TINY_RES)));
	}
	return (0);
}
