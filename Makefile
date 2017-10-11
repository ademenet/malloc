# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/11 16:56:30 by ademenet          #+#    #+#              #
#    Updated: 2017/10/11 17:12:18 by ademenet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

.PHONY: all test clean fclean re norme

CC = gcc

FLAGS = -Wall -Wextra -Werror

CPP_FLAGS = -I./inc

NAME = malloc

SRC_PATH = ./src
INC_PATH = ./inc
OBJ_PATH = ./obj

SRC_NAME =	allocations.c \
			bonus.c \
			free.c \
			main.c \
			malloc.c \
			realloc.c \
			show_mem_alloc.c \
			utils.c

INC_NAME = 

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -fPIC -shared -o libft_malloc_$(HOSTTYPE).so
	ln -sf libft_malloc_$(HOSTTYPE).so libft_malloc.so

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) -c $< $(CPP_FLAGS) -o $@ 

clean:
	rm -rf ./obj

fclean: clean
	rm -rf libft_malloc.so
	rm -rf libft_malloc_$(HOSTTYPE).so

re: fclean all

norme:
	@norminette */*[hc]
	@norminette *[hc]