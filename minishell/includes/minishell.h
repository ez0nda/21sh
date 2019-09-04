/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:35:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:58:16 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <functions.h>
# include <termios.h>
# include <term.h>
# include <sys/types.h>
# include <curses.h>
# include <signal.h>
# include "functions.h"
# include "struct.h"
# include "../libft/libft.h"

char **g_env;

#endif
