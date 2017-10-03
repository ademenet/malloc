/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:21:29 by ademenet          #+#    #+#             */
/*   Updated: 2017/10/03 18:24:04 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <pthread.h>
# include <stdio.h>
# include "libft/libft.h"

# include "dbg.h"
# include <stdlib.h>

# define MALLOC_MAX			((size_t)-1 - (2 * getpagesize()))

# define TINY_ZONE			(getpagesize() * 64)
# define TINY_RES			32
# define TINY_LIM			1024

# define SMALL_ZONE			(getpagesize() * 512)
# define SMALL_RES			512
# define SMALL_LIM			4096

# define HEADER_SIZE		(sizeof(t_block))
// # define ALIGN(size, res)	(((size) + ((res) - 1)) & ~((res) - 1))
# define ALIGN(size, res)	(((size) + ((res) - 1))/res)*(res)

# define PROT_SET			PROT_READ | PROT_WRITE
# define MAP_SET			MAP_ANON | MAP_PRIVATE
// # define ALIGN_LARGE(size)	((size) & (size - 1))

# define GRN				"\033[32;m"
# define RED				"\033[31;m"
# define END				"\033[0m"

typedef struct s_block		t_block;
typedef struct s_bin		t_bin;
typedef unsigned int		t_ui;
typedef enum e_type			t_type;

extern t_bin				g_bin;
extern pthread_mutex_t		g_fastmutex;

/*
** Structure of one block.
*/

struct	s_block 
{
	size_t					size;
	t_ui					free;
	t_block					*prev;
	t_block					*next;
};

/*
** This is our main global maintaining bins: tiny, small and large.
*/

struct	s_bin
{
	t_block					*tiny;
	t_block					*small;
	t_block					*large;
};

enum	e_type
{
	TINY,
	SMALL,
	LARGE
};

/*
** malloc
*/

static void					*allocate_large(size_t size);
static void					*find_fit(t_block *list, size_t true_size);
static t_block				*extend_heap(t_block *list, size_t size, size_t true_size, t_type type);
static t_block				*allocate(size_t size, t_block *list, t_type type);
static void					init_malloc(void);
void						*malloc_nts(size_t size);

void						free_nts(void *ptr);

/*
** utils
*/

void						display_list_of_blocks(t_block *list);

/*
** show_mem_alloc
*/

void						show_mem_alloc(void);
void						show_mem_alloc_all(void);

#endif
