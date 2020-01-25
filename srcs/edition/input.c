/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:12:15 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/12 11:36:44 by ezonda           ###   ########.fr       */
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

void			join_cmds(t_var *data, int index)
{
	data->cmds[index] = ft_strjoin(data->cmds[index],
			data->cmds[index + 1]);
	index++;
	while (data->cmds[index])
	{
		data->cmds[index] = data->cmds[index + 1];
		index++;
	}
}

void			realloc_pipe(t_var *data)
{
	int i;
	char *s1;
	char *s2;

	i = 0;
	s1 = NULL;
	s2 = ft_strdup(ft_strrchr(data->cmds[data->cmd_index], '|'));
	while (data->cmds[data->cmd_index][i] != '|')
		i++;
	s1 = ft_strnew(i);
	i = 0;
	while (data->cmds[data->cmd_index][i] != '|')
	{
		s1[i] = data->cmds[data->cmd_index][i];
		i++;
	}
	free(data->cmds[data->cmd_index]);
	data->cmds[data->cmd_index] = ft_strjoin_free(s1, s2, 2);

}

void			realloc_redir(t_var *data)
{
	int i;
	char *s1;
	char *s2;

	i = 0;
	s1 = NULL;
	s2 = ft_strdup(ft_strchr(data->cmds[data->cmd_index], '>'));
	while (data->cmds[data->cmd_index][i] != '>')
		i++;
	s1 = ft_strnew(i);
	i = 0;
	while (data->cmds[data->cmd_index][i] != '|')
	{
		s1[i] = data->cmds[data->cmd_index][i];
		i++;
	}
	free(data->cmds[data->cmd_index]);
	data->cmds[data->cmd_index] = ft_strjoin_free(s1, s2, 2);
}

void			manage_pipe(t_var *data)
{
	int i;
	int pipe;
	int redir;

	i = 0;
	pipe = 0;
	redir = 0;
	while (data->cmds[data->cmd_index][i])
	{
		if (data->cmds[data->cmd_index][i] == '|')
			pipe++;
		else if (data->cmds[data->cmd_index][i] == '>'
				|| data->cmds[data->cmd_index][i] == '<')
			redir++;
		i++;
	}
	if (pipe <= 1 && !redir)
	{
//		ft_printf("\nNOTHING\n");
		return ;
	}
	else if (redir && !pipe)
	{
//		ft_printf("\nREDIR NO PIPE\n");
		return ;
	}
	else if (pipe && redir)
	{
//		ft_printf("\nBOTH\n");
		realloc_redir(data);
	}
	else
	{
//		ft_printf("\nPIPE NO REDIR\n");
		realloc_pipe(data);
	}
}

void			launch_cmds(t_var *data)
{
	t_cmd	*cmd;

	data->cmd_index = 0;
	if (parse_error_pipe(data))
	{
		data->pos = 0;
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		return ;
	}
	check_first_last_char(data, 0);
	data->cmds = ft_split(data->lex_str, ';');
	check_single_pipes(data);
	check_first_last_char(data, 1);
	while (data->cmds[data->cmd_index])
	{
		manage_pipe(data);
		cmd = shell_parser(data->cmds[data->cmd_index]);
		get_cmd_type(cmd, data);
		data->cmd_index++;
	}
	data->pos = 0;
	if (data->lex_str)
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	free_tab(data->cmds);
}

void			init_cmds(t_var *data)
{
	if (ft_strlen(data->lex_str) != 0)
	{
		if (check_quotes(data) == 1)
			read_quotes(data, 0);
		add_to_history(data);
		launch_cmds(data);
		data->mod_quotes = 0;
	}
	else
		ft_putchar('\n');
	prompt(data);
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
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
		{
			ft_putchar(buffer[0]);
			add_to_string(buffer[0], data);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
			init_cmds(data);
		get_key(data, buffer);
	}
}
