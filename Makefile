.PHONY: all test clean fclean re norme

CC = gcc

FLAGS = -Wall -Wextra -Werror

CPP_FLAGS = -Iinclude

NAME = libft_malloc_$HOSTTYPE.so

SRC_PATH = ./src
INC_PATH = ./inc
OBJ_PATH = ./obj

SRC_NAME = 

INC_NAME = 

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(FLAGS) -o $@ $^ libft/libft.a libft/ft_printf/libftprintf.a
	@echo "\033[1;34mMalloc\t\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -c -o $@ $<

clean:
	@make clean -C libft
	@rm -rf ./obj correctme.sh
	@echo "\033[1;34mMalloc\t\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "\033[1;34mMalloc\t\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all

norme:
	@norminette */*[hc]