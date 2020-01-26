/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:13:18 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:03:12 by ezonda           ###   ########.fr       */
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
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	data->n_prompt = 0;
}

void		pipe_prompt(t_var *data, int index)
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
			data->lex_str = ft_strjoin_free(data->lex_str, &buffer[0], 0);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
			break ;
		get_key(data, buffer);
	}
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
	data->h_prompt = 0;
}
