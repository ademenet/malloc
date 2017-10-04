/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:59:43 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/04 12:13:40 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		test_large(void)
{
	char 	*test1;
	char 	*test2;
	char 	*test3;
	int		i = 0;

	test1 = (char*)malloc_nts(5000);
	for (i = 0; i < 5000; i++) {
		test1[i] = 'a';
	}
	test2 = (char*)malloc_nts(7000);
	for (i = 0; i < 7000; i++) {
		test2[i] = 'a';
	}
	test3 = (char*)malloc_nts(8000);
	for (i = 0; i < 8000; i++) {
		test2[i] = 'a';
	}
	printf("%s%s%s\n", test1, test2, test3);	
}

void		test_large_loop(void)
{
	int		param = 5000;
	int		max = 50;
	int		i;
	char	*test;

	for (i = 0; i < max; i++) {
		test = (char*)malloc_nts(param);
		test[0] = 'a';
	}
}

void		test_small(void)
{
	char	*test1;
	char	*test2;
	int		i = 0;

	test1 = (char*)malloc_nts(2300);
	for (i = 0; i < 2300; i++) {
		test1[i] = 'a';
	}
	test2 = (char*)malloc_nts(1050);
	for (i = 0; i < 1050; i++) {
		test2[i] = 'b';
	}
	printf("%s%s\n", test1, test2);		
}

void		test_tiny(void)
{
	char	*test1;
	char	*test2;
	int		i = 0;

	test1 = (char*)malloc_nts(23);
	for (i = 0; i < 23; i++) {
		test1[i] = 'a';
	}
	test2 = (char*)malloc_nts(2);
	for (i = 0; i < 2; i++) {
		test2[i] = 'b';
	}
	printf("%s%s\n", test1, test2);		
}

void		test_loop_tiny(void)
{
	int		param = 32;
	int		max = 8192;
	int		i;
	char	*test;

	for (i = 0; i < max; i++) {
		test = (char*)malloc_nts(param);
		test[0] = 'a';
	}
}

void		test_nul(void)
{
	printf("HEADER_SIZE = %zu\n", HEADER_SIZE);
	printf("TINY_ZONE = %d\n", TINY_ZONE);
	printf("SMALL_ZONE = %d\n", SMALL_ZONE);
	printf("TINY_ZONE %% TINY_RES = %d\n", TINY_ZONE % TINY_RES);
	printf("SMALL_ZONE %% SMALL_RES = %d\n", SMALL_ZONE % SMALL_RES);
	printf("TINY_ZONE / TINY_RES = %d\n", TINY_ZONE / TINY_RES);
	printf("SMALL_ZONE / SMALL_RES = %d\n", SMALL_ZONE / SMALL_RES);
	printf("ALIGN(33, 32) = %d\n", ALIGN(33, 32));
	printf("ALIGN(67, 32) = %d\n", ALIGN(67, 32));
	printf("ALIGN(32, 32) = %d\n", ALIGN(32, 32));
	printf("ALIGN(33, 32) = %d\n", ALIGN(33, 32));
	printf("ALIGN(0, 32) = %d\n", ALIGN(0, 32));
	printf("ALIGN(1, 32) = %d\n", ALIGN(1, 32));
}

int			main(void)
{
	// test_large();
	test_large_loop();
	// test_tiny();
	// test_small();
	// test_loop_tiny();
	show_mem_alloc();
	// show_mem_alloc_all();
	// test_nul();
	return (0);
}
