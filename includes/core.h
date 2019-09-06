/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:00:44 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/05 12:19:02 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "../libft/includes/libft.h"

# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>

# include "edition.h"
# include "tools.h"

# define BUFF_SIZE 4096

t_var			*update_data(int mod, t_var *data);
int				exit_shell(void);
void			set_termcanon(t_var *data);

void			signal_handler(void);

#endif
