# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 15:01:03 by heynard           #+#    #+#              #
#    Updated: 2018/12/07 10:45:30 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc

NAME = libft_malloc_$(HOSTTYPE).so
NAME_LINK = libft_malloc.so

PATH_SRC = ./srcs/

PATH_INC = ./includes/

CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L ./libft/ -lft
IFLAGS = -I $(PATH_INC)
LDFLAGS = -shared

SRC = ft_malloc.c\
		ft_realloc.c\
		ft_free.c\
		show_alloc_mem.c\
		search_block.c\
		block_function.c\
		area_functions.c\
		align_bit.c
OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	$(CC) $(IFLAGS) $(OBJ) -o $(NAME) $(CFLAGS) $(LFLAGS) $(LDFLAGS)
	ln -s $(NAME) $(NAME_LINK)

%.o: %.c
	@$(CC) $(IFLAGS) -o $@ -c $< $(CFLAGS)
	@echo "\033[1;34m" $@ "\033[0m\t\t\t\033[1;32m[OK]\033[0m"

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)
	rm -f $(NAME_LINK)

re: fclean all
