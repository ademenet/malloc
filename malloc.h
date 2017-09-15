#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/resource.h>
# include <sys/mman.h>

typedef struct s_block *t_block;

struct sblock {
    size_t      size;
    t_block     next;
    int         free;
}

#endif