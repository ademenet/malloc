/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:21:29 by ademenet          #+#    #+#             */
/*   Updated: 2017/09/27 17:59:44 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <stdio.h>

# define TINY_SIZE			(get_page_size() * 64)
# define SMALL_SIZE			(get_page_size() * 512)
# define TINY_RES			32
# define SMALL_RES			512
# define ALIGN_TINY(size)	(((size) + (TINY_RES - 1)) & ~(TINY_RES - 1))
# define ALIGN_SMALL(size)	(((size) + (SMALL_RES - 1)) & ~(SMALL_RES - 1))
# define ALIGN_LARGE(size)	((size) & (size - 1))

typedef struct 	s_block		*t_block;
typedef struct s_bin		*t_bin;
typedef enum e_type			*t_type;
typedef unsigned int		t_ui;

struct	s_block {
	size_t					size;
	t_block					*next;
	t_block					*prev;
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
