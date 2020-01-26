# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/12 09:46:09 by ezonda       #+#   ##    ##    #+#        #
#    Updated: 2020/01/22 19:41:33 by dzonda      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libft.a

LIBPRINTF = srcs/printf/libftprintf.a

SRCDIR = srcs
OBJDIR = objs
INCDIR = includes

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE

AR = ar rcs
LIBTOOL = libtool -static
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wunused -Wunreachable-code

SUBDIR = \
		convert \
		display \
		get_next_line \
		is \
		lst \
		math \
		memory \
		printf/core \
		printf/lib \
		string

SUBFILE = \
		convert/ft_atoi.c \
		convert/ft_itoa.c \
		convert/ft_tolower.c \
		convert/ft_toupper.c \
		\
		display/ft_print_words_tables.c \
		display/ft_putchar.c \
		display/ft_putchar_fd.c \
		display/ft_putendl.c \
		display/ft_putendl_fd.c \
		display/ft_putnbr.c \
		display/ft_putnbr_fd.c \
		display/ft_putstr.c \
		display/ft_putstr_fd.c \
		\
		get_next_line/get_next_line.c \
		\
		is/ft_is_prime.c \
		is/ft_isalnum.c \
		is/ft_isalpha.c \
		is/ft_isascii.c \
		is/ft_isdigit.c \
		is/ft_isprint.c \
		is/ft_is_dir.c \
		\
		lst/ft_lstadd.c \
		lst/ft_lstdel.c \
		lst/ft_lstdelone.c \
		lst/ft_lstiter.c \
		lst/ft_lstmap.c \
		lst/ft_lstnew.c \
		\
		math/ft_recursive_power.c \
		math/ft_sqrt.c \
		\
		memory/ft_bzero.c \
		memory/ft_memalloc.c \
		memory/ft_memccpy.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_memcpy.c \
		memory/ft_memdel.c \
		memory/ft_memmove.c \
		memory/ft_memset.c \
		\
		printf/core/ft_dispatch.c \
		printf/core/ft_flag_u.c \
		printf/core/ft_float.c \
		printf/core/ft_hexa.c \
		printf/core/ft_indic_csp.c \
		printf/core/ft_indic_mod.c \
		printf/core/ft_octal.c \
		printf/core/ft_parser.c \
		printf/core/ft_parser.c \
		printf/core/ft_print_numbers.c \
		printf/core/ft_printf.c \
		printf/core/ft_tools.c \
		printf/core/ft_tools2.c \
		printf/core/ft_unsigned.c \
		printf/lib/pf_atoi.c \
		printf/lib/pf_isdigit.c \
		printf/lib/pf_itoa.c \
		printf/lib/pf_putchar.c \
		printf/lib/pf_putnbr.c \
		printf/lib/pf_putstr.c \
		printf/lib/pf_strcmp.c \
		printf/lib/pf_strdup.c \
		printf/lib/pf_strlen.c \
		printf/lib/pf_strnew.c \
		printf/lib/pf_strrev.c \
		printf/lib/pf_strsub.c \
		\
		string/ft_strcat.c \
		string/ft_strchr.c \
		string/ft_strclr.c \
		string/ft_strcmp.c \
		string/ft_strcpy.c \
		string/ft_strdel.c \
		string/ft_strdup.c \
		string/ft_strndup.c \
		string/ft_strequ.c \
		string/ft_striter.c \
		string/ft_striteri.c \
		string/ft_strjoin.c \
		string/ft_strjoin_free.c \
		string/ft_strlcat.c \
		string/ft_strlen.c \
		string/ft_strmap.c \
		string/ft_strmapi.c \
		string/ft_strncat.c \
		string/ft_strncmp.c \
		string/ft_strncpy.c \
		string/ft_strnequ.c \
		string/ft_strnew.c \
		string/ft_strnstr.c \
		string/ft_strrchr.c \
		string/ft_strrev.c \
		string/ft_strsplit.c \
		string/ft_split_ws.c \
		string/ft_split.c \
		string/ft_strstr.c \
		string/ft_strsub.c \
		string/ft_strtrim.c

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = -I$(INCDIR)

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null

# Old rules to link to lib
# $(HIDE)echo $(MAKEFILE_NAME): "Linking \t ->" $@ $(LIBPRINTF)
# $(HIDE)$(MAKE) -C srcs/printf
# $(HIDE)$(LIBTOOL) -o $(NAME) $(NAME) $(LIBPRINTF)

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJDIRS) $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): "Linking \t ->" $@
	$(HIDE)$(AR) $(NAME) $(OBJS)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo $(MAKEFILE_NAME): "Building \t ->" $@
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	@echo $(MAKEFILE_NAME): "Making \t ->" $(OBJDIRS)
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

clean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(MAKE) -C srcs/printf clean
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	$(HIDE)$(MAKE) -C srcs/printf fclean
 	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all
