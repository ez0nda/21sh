/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:00:44 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/15 13:59:20 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "../libft/includes/libft.h"

# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>

# include "edition.h"
# include "tools.h"
# include "parser.h"
# include "execute.h"
# include "builtins.h"

# define BUFF_SHELL 4096

t_var			*update_data(int mod, t_var *data);
int				exit_shell(t_var *data);
void			set_termcanon(t_var *data);

void			signal_handler(void);

#endif
