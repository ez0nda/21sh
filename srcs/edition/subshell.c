/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:13:18 by ezonda            #+#    #+#             */
/*   Updated: 2019/12/14 10:34:48 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void			cursh_prompt(t_var *data)
{
	char buffer[6];

	data->c_prompt = 1;
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
			if (data->lex_str[ft_strlen(data->lex_str) - 1] == '}')
				break ;
			add_to_here_stock(';', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
	free(data->lex_str);
	data->lex_str = ft_strdup(data->here_stock);
	rm_char(data->lex_str, '}');
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	data->c_prompt = 0;
}

void			new_prompt(t_var *data)
{
	char buffer[6];

	if (!data->n_prompt)
		data->here_stock = ft_strjoin(data->here_stock, data->lex_str);
	data->n_prompt = 1;
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
			check_single_pipes(data);
			check_first_last_char(data, 1);
			break ;
		}
		get_key(data, buffer);
	}
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	data->n_prompt = 0;
}

void			pipe_prompt(t_var *data, int index)
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

void		heredoc_prompt(t_var *data)
{
	char buffer[6];

	data->h_prompt = 1;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
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
			ft_putchar('\n');
			if (!ft_strcmp(data->lex_str, data->herend))
			{
				rm_herend(data);
				break ;
			}
			add_to_here_stock('\n', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		}
		get_key(data, buffer);
	}
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	data->h_prompt = 0;
}
