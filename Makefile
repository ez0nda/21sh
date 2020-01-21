# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 09:27:41 by ezonda            #+#    #+#              #
#    Updated: 2020/01/21 09:27:43 by ezonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCDIR = srcs
OBJDIR = objs
INCDIR = includes
LIBDIR = libft

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE

CC = gcc
CFLAGS = # -Wall -Wextra -Werror -Wunused -Wunreachable-code
LDFLAGS = -Llibft 
LDLIBS = -lft -ltermcap

SUBDIR = \
		core \
		edition \
		parser \
		execute \
		builtins

SUBFILE = \
		core/main.c \
		core/signal.c \
		\
		edition/input.c \
		edition/history.c \
		edition/arrows.c \
		edition/prompt.c \
		edition/edit.c \
		edition/skip.c \
		edition/subshell.c \
		edition/copy_paste.c \
		edition/edition_tools.c \
		\
		parser/constructors.c \
		parser/parser.c \
		parser/tokenizer.c \
		parser/parser_tools.c \
		parser/quotes.c \
		\
		execute/exec_cmd.c \
		execute/execute_tools.c \
		execute/file_manage.c \
		execute/init_excute.c \
		execute/cmd_type.c \
		\
		builtins/env.c \
		builtins/setenv.c \
		builtins/unsetenv.c \
		builtins/cd.c \
		builtins/tools.c \
		builtins/echo.c

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = -I$(INCDIR)

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS := $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif
MAKE = make -C
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null

.PHONY: all clean fclean re lib

all: lib $(NAME)

$(NAME): $(OBJDIRS) $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): "Linking \t ->" $@
	$(HIDE)$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo $(MAKEFILE_NAME): "Building \t ->" $@
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	@echo $(MAKEFILE_NAME): "Making \t ->" $(OBJDIRS)
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

lib:
	$(HIDE)$(MAKE) $(LIBDIR)

clean:
	$(HIDE)$(MAKE) $(LIBDIR) clean
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	$(HIDE)$(MAKE) $(LIBDIR) fclean
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all
