# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:46:09 by ezonda            #+#    #+#              #
#    Updated: 2019/08/29 11:41:22 by ezonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

NAME2 = srcs/printf/libftprintf.a

SRC = srcs/convert/ft_atoi.c \
	  srcs/convert/ft_itoa.c \
	  srcs/convert/ft_tolower.c \
	  srcs/convert/ft_toupper.c \
	  \
	  srcs/display/ft_print_words_tables.c \
	  srcs/display/ft_putchar.c \
	  srcs/display/ft_putchar_fd.c \
	  srcs/display/ft_putendl.c \
	  srcs/display/ft_putendl_fd.c \
	  srcs/display/ft_putnbr.c \
	  srcs/display/ft_putnbr_fd.c \
	  srcs/display/ft_putstr.c \
	  srcs/display/ft_putstr_fd.c \
	  \
	  srcs/get_next_line/get_next_line.c \
	  \
	  srcs/is/ft_is_prime.c \
	  srcs/is/ft_isalnum.c \
	  srcs/is/ft_isalpha.c \
	  srcs/is/ft_isascii.c \
	  srcs/is/ft_isdigit.c \
	  srcs/is/ft_isprint.c \
		srcs/is/ft_is_dir.c \
	  \
	  srcs/lst/ft_lstadd.c \
	  srcs/lst/ft_lstdel.c \
	  srcs/lst/ft_lstdelone.c \
	  srcs/lst/ft_lstiter.c \
	  srcs/lst/ft_lstmap.c \
	  srcs/lst/ft_lstnew.c \
	  \
	  srcs/math/ft_recursive_power.c \
	  srcs/math/ft_sqrt.c \
	  \
	  srcs/memory/ft_bzero.c \
	  srcs/memory/ft_memalloc.c \
	  srcs/memory/ft_memccpy.c \
	  srcs/memory/ft_memchr.c \
	  srcs/memory/ft_memcmp.c \
	  srcs/memory/ft_memcpy.c \
	  srcs/memory/ft_memdel.c \
	  srcs/memory/ft_memmove.c \
	  srcs/memory/ft_memset.c \
	  \
	  srcs/string/ft_strcat.c \
	  srcs/string/ft_strchr.c \
	  srcs/string/ft_strclr.c \
	  srcs/string/ft_strcmp.c \
	  srcs/string/ft_strcpy.c \
	  srcs/string/ft_strdel.c \
	  srcs/string/ft_strdup.c \
		srcs/string/ft_strndup.c \
	  srcs/string/ft_strequ.c \
	  srcs/string/ft_striter.c \
	  srcs/string/ft_striteri.c \
	  srcs/string/ft_strjoin.c \
		srcs/string/ft_strjoin_free.c \
	  srcs/string/ft_strlcat.c \
	  srcs/string/ft_strlen.c \
	  srcs/string/ft_strmap.c \
	  srcs/string/ft_strmapi.c \
	  srcs/string/ft_strncat.c \
	  srcs/string/ft_strncmp.c \
	  srcs/string/ft_strncpy.c \
	  srcs/string/ft_strnequ.c \
	  srcs/string/ft_strnew.c \
	  srcs/string/ft_strnstr.c \
	  srcs/string/ft_strrchr.c \
	  srcs/string/ft_strrev.c \
	  srcs/string/ft_strsplit.c \
	  srcs/string/ft_split_ws.c \
		srcs/string/ft_split.c \
	  srcs/string/ft_strstr.c \
	  srcs/string/ft_strsub.c \
	  srcs/string/ft_strtrim.c \

# OBJ = $(SRC:.c=.o)

OBJ = ft_atoi.o \
	  ft_itoa.o \
	  ft_tolower.o \
	  ft_toupper.o \
	  \
	  ft_print_words_tables.o \
	  ft_putchar.o \
	  ft_putchar_fd.o \
	  ft_putendl.o \
	  ft_putendl_fd.o \
	  ft_putnbr.o \
	  ft_putnbr_fd.o \
	  ft_putstr.o \
	  ft_putstr_fd.o \
	  \
	  get_next_line.o \
	  \
	  ft_is_prime.o \
		ft_is_dir.o \
	  ft_isalnum.o \
	  ft_isalpha.o \
	  ft_isascii.o \
	  ft_isdigit.o \
	  ft_isprint.o \
	  \
	  ft_lstadd.o \
	  ft_lstdel.o \
	  ft_lstdelone.o \
	  ft_lstiter.o \
	  ft_lstmap.o \
	  ft_lstnew.o \
	  \
	  ft_recursive_power.o \
	  ft_sqrt.o \
	  \
	  ft_bzero.o \
	  ft_memalloc.o \
	  ft_memccpy.o \
	  ft_memchr.o \
	  ft_memcmp.o \
	  ft_memcpy.o \
	  ft_memdel.o \
	  ft_memmove.o \
	  ft_memset.o \
	  \
	  ft_strcat.o \
	  ft_strchr.o \
	  ft_strclr.o \
	  ft_strcmp.o \
	  ft_strcpy.o \
	  ft_strdel.o \
	  ft_strdup.o \
		ft_strndup.o \
	  ft_strequ.o \
	  ft_striter.o \
	  ft_striteri.o \
	  ft_strjoin.o \
		ft_strjoin_free.o \
	  ft_strlcat.o \
	  ft_strlen.o \
	  ft_strmap.o \
	  ft_strmapi.o \
	  ft_strncat.o \
	  ft_strncmp.o \
	  ft_strncpy.o \
	  ft_strnequ.o \
	  ft_strnew.o \
	  ft_strnstr.o \
	  ft_strrchr.o \
	  ft_strrev.o \
	  ft_strsplit.o \
	  ft_split_ws.o \
		ft_split.o \
	  ft_strstr.o \
	  ft_strsub.o \
	  ft_strtrim.o \


CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -c $(SRC)
	@make -C srcs/printf/
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@libtool -static -o $(NAME) $(NAME) $(NAME2)

%.o: %.c
	@$(CC) $(FLAGS) $@ -c $< $(FLAGS)

clean:
	@make clean -C srcs/printf/
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C srcs/printf/
	@rm -f $(NAME)

re: fclean all
