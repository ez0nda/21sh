/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:12:15 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/24 12:36:58 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int				check_overflow(t_var *data)
{
	if (data->char_count >= BUFF_SHELL)
	{
		ft_putstr_fd("\n21sh: buffer overflow: ", STDERR_FILENO);
		ft_putendl_fd("command line has too many characters", STDERR_FILENO);
		data->pos = 0;
		data->char_count = 0;
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		prompt(data);
		return (0);
	}
	return (1);
}

static void		get_copy_paste(t_var *data, char *buffer)
{
	if (!ft_strcmp(buffer, OPT_S))
		select_mode(data);
	if (!ft_strcmp(buffer, OPT_C))
		copy_cut_mode(data, 0);
	if (!ft_strcmp(buffer, OPT_X))
		copy_cut_mode(data, 1);
	if (!ft_strcmp(buffer, OPT_V))
		paste_mode(data);
}

void		get_key(t_var *data, char *buffer)
{
	if (!ft_strcmp(buffer, KEY_L))
		move_left(data);
	if (!ft_strcmp(buffer, KEY_R))
		move_right(data);
	if (!ft_strcmp(buffer, KEY_U))
		show_history(data, 1);
	if (!ft_strcmp(buffer, KEY_D))
		show_history(data, 2);
	if (!ft_strcmp(buffer, OPT_L))
		jump(data, 1);
	if (!ft_strcmp(buffer, OPT_R))
		jump(data, 2);
	if (!ft_strcmp(buffer, OPT_U))
		move_up(data);
	if (!ft_strcmp(buffer, OPT_D))
		move_down(data);
	if (!ft_strcmp(buffer, DEL))
		remove_cur_char(data);
	if (!ft_strcmp(buffer, UNDO))
		remove_prev_char(data);
	if (!ft_strcmp(buffer, HOME))
		move_first_last(data, 1);
	if (!ft_strcmp(buffer, END))
		move_first_last(data, 2);
	get_copy_paste(data, buffer);
}

void			launch_cmds(t_var *data)
{
	t_cmd	*cmd;

	data->cmd_index = 0;
	data->cmds = ft_strsplit(data->lex_str, ';');
	while (data->cmds[data->cmd_index])
	{
		cmd = shell_parser(data->cmds[data->cmd_index]);
		get_cmd_type(cmd, data);
		data->cmd_index++;
	}
	data->pos = 0;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	free_tab(data->cmds);
}

void			get_input(t_var *data)
{
	char buffer[6];

	prompt(data);
	while (1)
	{
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
		{
			ft_putchar(buffer[0]);
			add_to_string(buffer[0], data);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			if (ft_strlen(data->lex_str) != 0)
			{
				if (check_quotes(data) == 1)
					read_quotes(data);
				add_to_history(data);
				launch_cmds(data);
			}
			else
				ft_putchar('\n');
			prompt(data);
		}
		get_key(data, buffer);
	}
}
