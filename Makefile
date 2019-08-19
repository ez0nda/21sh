# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 11:30:32 by ezonda            #+#    #+#              #
#    Updated: 2019/08/19 12:26:49 by ezonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = srcs/main.c \
	  srcs/tools.c \
	  srcs/input.c \
	  srcs/signal.c \

OBJ = srcs/main.o \
	  srcs/tools.o \
	  srcs/input.o \
	  srcs/signal.o \

LIB = libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -l termcap

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(FLAGS) $(LIB) -I./libft $(OBJ) -I./includes -o $(NAME)

$(LIB):
	make -C libft/ fclean
	make -C libft

%.o: %.c
	$(CC) -o $@ -c $< -I./includes

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all

