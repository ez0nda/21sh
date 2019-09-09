# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 11:30:32 by ezonda            #+#    #+#              #
#    Updated: 2019/09/09 11:07:49 by ezonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = srcs/core/main.c \
	  srcs/core/signal.c \
	  srcs/tools/edition_tools.c \
	  srcs/edition/input.c \
	  srcs/edition/history.c \
	  srcs/edition/arrows.c \
	  srcs/edition/prompt.c \
	  srcs/edition/edit.c \
	  srcs/edition/skip.c \
	  srcs/edition/copy_paste.c \

OBJ = srcs/core/main.o \
	  srcs/core/signal.o \
	  srcs/tools/edition_tools.o \
	  srcs/edition/input.o \
	  srcs/edition/history.o \
	  srcs/edition/arrows.o \
	  srcs/edition/prompt.o \
	  srcs/edition/edit.o \
	  srcs/edition/skip.o \
	  srcs/edition/copy_paste.o \

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
