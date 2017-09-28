/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:21:29 by ademenet          #+#    #+#             */
/*   Updated: 2017/09/28 18:26:16 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <pthread.h>
# include <stdio.h>

# define MALLOC_MAX			((size_t)-1 - (2 * getpagesize()))

# define TINY_SIZE			(getpagesize() * 64)
# define TINY_RES			32
# define TINY_LIM			1024

# define SMALL_SIZE			(getpagesize() * 512)
# define SMALL_RES			512
# define SMALL_LIM			4096

# define HEADER_SIZE		(sizeof(t_block))
# define ALIGN(size, res)	(((size) + ((res) - 1)) & ~((res) - 1))

# define PROT_SET			PROT_READ | PROD_WRITE
# define MAP_SET			MAP_ANON | MAN_PRIVATE
// # define ALIGN_LARGE(size)	((size) & (size - 1))

typedef struct s_block		t_block;
typedef struct s_bin		t_bin;
typedef enum e_type			t_type;
typedef unsigned int		t_ui;

extern t_bin				g_bin;
extern pthread_mutex_t		g_fastmutex;

/*
** Structure of one block.
*/

struct	s_block {
	size_t					size;
	t_block					*next;
	t_ui					free;
};

struct	s_bin
{
	t_block					*tiny;
	t_block					*small;
	t_block					*large;
};

enum	e_alloc_type
{
	TINY,
	SMALL,
	LARGE,
	NONE
};

void						free(void *ptr);
void						*malloc(size_t size);

#endif
