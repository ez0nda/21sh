/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:19:08 by ezonda            #+#    #+#             */
/*   Updated: 2019/08/19 13:58:56 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../libft/includes/libft.h"

# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

struct termios		term;
struct termios		og_term;

typedef struct	s_var
{
	char	**environ;
	int		pos;
}				t_var;

char			**ft_tabdup(char **tab);
void			get_input(t_var *data);
void			signal_handler(void);
t_var			*update_data(int mod, t_var *data);
int				exit_shell(void);
void			set_termcanon(t_var *data);
void			get_input(t_var *data);
void			init_shell(t_var *data);

#endif
