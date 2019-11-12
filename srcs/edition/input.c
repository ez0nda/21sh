/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:12:15 by ezonda            #+#    #+#             */
/*   Updated: 2019/11/12 04:32:52 by ezonda           ###   ########.fr       */
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
	if (!ft_strcmp(buffer, CTRL_D))
	{
		if (data->lex_str[0])
			remove_cur_char(data);
		else
			exit_shell(data);
	}
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

void			get_last_pipe(t_var *data, int index)
{
	char buffer[6];

	data->p_prompt = 1;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
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
			data->lex_str = ft_strjoin(data->lex_str, &buffer[0]);
			data->pos = ft_strlen(data->lex_str);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
			break ;
		get_key(data, buffer);
	}
	data->cmds[index] = ft_strjoin_free(data->cmds[index], data->lex_str, 0);
	check_single_pipes(data);
	data->p_prompt = 0;
}

void			join_cmds(t_var *data, int index)
{
	data->cmds[index] = ft_strjoin_free(data->cmds[index], data->cmds[index + 1], 0);
	index++;
	while (data->cmds[index])
	{
		data->cmds[index] = data->cmds[index + 1];
		index++;
	}
}

void			new_line(t_var *data)
{
	char buffer[6];

	data->n_prompt = 1;
	data->here_stock = ft_strjoin(data->here_stock, data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	while (1)
	{
		prompt(data);
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
		{
			ft_putchar(buffer[0]);
			add_to_here_stock(buffer[0], data);
			data->lex_str = ft_strjoin(data->lex_str, &buffer[0]);
			data->pos = ft_strlen(data->lex_str);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
				rm_char(data->here_stock, '\\');
				data->cmds[ft_tablen(data->cmds) - 1] = ft_strdup(data->here_stock);
			if (!check_last_char(data))
			{
				ft_printf("\nstock1 : {%s}\n", data->here_stock);
				break ;
			}
			else
				ft_printf("\nstock2 : {%s}\n", data->here_stock);
		}
		get_key(data, buffer);
	}
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	data->n_prompt = 0;
}

void			check_single_pipes(t_var *data)
{
	int i;
	int len;
	int last_cmd;

	i = 0;
	len = 0;
	last_cmd = 0;
	last_cmd = ft_tablen(data->cmds) - 1;
	while (i <= last_cmd)
	{
		last_cmd = ft_tablen(data->cmds) - 1;
		len = ft_strlen(data->cmds[i]) - 1;
		while (is_whitespaces(data->cmds[i][len]))
			len--;
		if (data->cmds[i][len] == '|' && i != last_cmd)
			join_cmds(data, i);
		else
			i++;
	}
	if (data->cmds[last_cmd][len] == '|')
	{
		ft_putchar('\n');
		get_last_pipe(data, last_cmd);
	}
}

int			check_last_char(t_var *data)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(data->lex_str) - 1;
	if (data->lex_str[len] == 92)
	{
		ft_putchar('\n');
		new_line(data);
		return (1);
	}
	return (0);
}

void			launch_cmds(t_var *data)
{
	t_cmd	*cmd;

	data->cmd_index = 0;
	data->cmds = ft_strsplit(data->lex_str, ';');
	check_single_pipes(data);
	check_last_char(data);
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
