# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/16 11:36:59 by ezonda       #+#   ##    ##    #+#        #
#    Updated: 2020/01/22 19:21:24 by dzonda      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = src
OBJDIR = obj
INCDIR = includes

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE

AR = ar rcs
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SUBDIR = \
		core \
		lib

SUBFILE = \
		core/ft_printf.c \
		core/ft_dispatch.c \
		core/ft_float.c \
		core/ft_hexa.c \
		core/ft_indic_csp.c \
		core/ft_octal.c \
		core/ft_parser.c \
		core/ft_print_numbers.c \
		core/ft_unsigned.c \
		core/ft_indic_mod.c \
		core/ft_flag_u.c \
		core/ft_tools.c \
		core/ft_tools2.c \
		lib/pf_atoi.c \
		lib/pf_isdigit.c \
		lib/pf_itoa.c \
		lib/pf_putchar.c \
		lib/pf_putnbr.c \
		lib/pf_putstr.c \
		lib/pf_strnew.c \
		lib/pf_strrev.c \
		lib/pf_strlen.c \
		lib/pf_strdup.c \
		lib/pf_strcmp.c \
		lib/pf_strsub.c

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
	@echo $(MAKEFILE_NAME): "Making \t\t ->" $(OBJDIRS)
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

clean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all