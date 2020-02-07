/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:05:11 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/05 13:39:53 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	display_subshells(t_var *data, char *buffer)
{
	ft_putchar(buffer[0]);
	add_this(buffer, data);
	data->char_count++;
}

void	init_subshells(t_var *data, char *buffer)
{
	get_curs_pos(data, data->pos);
	prompt(data);
	update_data(0, data);
	ft_bzero(buffer, 6);
	get_winsize(data);
	check_overflow(data);
}

void	cursh_loop(t_var *data)
{
	char buffer[6];

	while (1)
	{
		init_subshells(data, buffer);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
			display_subshells(data, buffer);
		if (data->reset == 1)
			break ;
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
		{
			data->here_stock = ft_strjoin_free(data->here_stock
					, data->lex_str, 0);
			if (data->lex_str[ft_strlen(data->lex_str) - 1] == '}')
				break ;
			data->pos = 0;
			add_to_here_stock(';', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
}

void	newline_loop(t_var *data)
{
	char buffer[6];

	while (1)
	{
		init_subshells(data, buffer);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
			display_subshells(data, buffer);
		if (data->reset == 1)
			break ;
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
		{
			data->here_stock = ft_strjoin_free(data->here_stock
					, data->lex_str, 0);
			rm_char(data->here_stock, '\\');
			free(data->cmds[ft_tablen(data->cmds) - 1]);
			data->cmds[ft_tablen(data->cmds) - 1] = ft_strdup(data->here_stock);
			check_single_pipes(data);
			check_first_last_char(data, 1);
			data->pos = 0;
			break ;
		}
		get_key(data, buffer);
	}
}

void	heredoc_loop(t_var *data)
{
	char buffer[6];

	while (1)
	{
		init_subshells(data, buffer);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
			display_subshells(data, buffer);
		if (data->reset == 1)
			break ;
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
		{
			ft_putchar('\n');
			data->here_stock = ft_strjoin_free(data->here_stock
					, data->lex_str, 0);
			if (!ft_strcmp(data->lex_str, data->herend))
			{
				rm_herend(data);
				break ;
			}
			data->pos = 0;
			add_to_here_stock('\n', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		}
		get_key(data, buffer);
	}
}
