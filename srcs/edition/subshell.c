/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:13:18 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/06 09:31:05 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void		cursh_prompt(t_var *data)
{
	data->c_prompt = 1;
	if (!data->here_stock)
		data->here_stock = ft_strnew(BUFF_SHELL);
	data->pos = 0;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	cursh_loop(data);
	if (data->reset == 1)
		get_input(data);
	ft_strdel(&data->lex_str);
	data->lex_str = ft_strdup(data->here_stock);
	rm_char(data->lex_str, '}');
	ft_strdel(&data->here_stock);
	data->c_prompt = 0;
}

void		new_prompt(t_var *data)
{
	if (!data->n_prompt && data->here_stock)
		data->here_stock = ft_strjoin_free(data->here_stock, data->lex_str, 0);
	data->n_prompt = 1;
	data->pos = 0;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	newline_loop(data);
	if (data->reset == 1)
		get_input(data);
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	data->n_prompt = 0;
}

void		pipe_prompt(t_var *data, int index)
{
	char buffer[6];

	data->p_prompt = 1;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	data->pos = 0;
	prompt(data);
	while (1)
	{
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
			display_subshells(data, buffer);
		if (data->reset == 1)
			break ;
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
		{
			data->pos = 0;
			break ;
		}
		get_key(data, buffer);
	}
	if (data->reset == 1)
		get_input(data);
	data->cmds[index] = ft_strjoin_free(data->cmds[index], data->lex_str, 0);
	check_single_pipes(data);
	data->p_prompt = 0;
}

void		heredoc_prompt(t_var *data)
{
	data->h_prompt = 1;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	if (!data->here_stock)
		data->here_stock = ft_strnew(BUFF_SHELL);
	data->pos = 0;
	heredoc_loop(data);
	if (data->reset == 1)
		get_input(data);
	data->cmds[data->cmd_index] = ft_strjoin_free(data->cmds[data->cmd_index],
			data->here_stock, 0);
	data->h_prompt = 0;
}
