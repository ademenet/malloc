#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <stdio.h>

# define TINY	8
# define SMALL	16
# define LARGE	236

typedef struct		s_block 		*t_block;
typedef struct		s_bin			*t_bin;
typedef enum		e_alloc_type	*t_alloc_type;

struct s_block {
    size_t			size;
    t_block			next;
    unsigned int	free;
};

struct s_bin
{
	void			*tiny;
	void			*small;
	void			*large;
};

enum	e_alloc_type;
{
	TINY,
	SMALL,
	LARGE,
	NONE
};

void		free(void *ptr);
void		*malloc(size_t size);

#endif