# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 11:36:59 by ezonda            #+#    #+#              #
#    Updated: 2019/01/29 16:40:18 by jebrocho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_dispatch.c ft_float.c ft_hexa.c ft_indic_csp.c ft_octal.c \
	ft_parser.c ft_print_numbers.c ft_unsigned.c ft_indic_mod.c ft_flag_u.c \
	ft_tools.c ft_tools2.c

LIB_SRC = lib/pf_atoi.c lib/pf_isdigit.c lib/pf_itoa.c lib/pf_putchar.c \
	lib/pf_putnbr.c lib/pf_putstr.c lib/pf_strnew.c lib/pf_strrev.c \
	lib/pf_strlen.c lib/pf_strdup.c lib/pf_strcmp.c lib/pf_strsub.c

OBJ = $(SRC:.c=.o)

LIB_OBJ = pf_atoi.o pf_isdigit.o pf_itoa.o pf_putchar.o pf_putnbr.o pf_putstr.o\
		  pf_strnew.o pf_strrev.o pf_strlen.o pf_strdup.o pf_strcmp.o \
		  pf_strsub.o

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -c $(SRC) $(LIB_SRC)
	@ar rc $(NAME) $(OBJ) $(LIB_OBJ)
	@ranlib $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS) -I./includes

clean:
	@rm -f $(OBJ)
	@rm -f $(LIB_OBJ)

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(LIB_OBJ)
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
