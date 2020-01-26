/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:35:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 12:39:39 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	parse_multi_quotes(t_var *data, int index)
{
	char *stock;

	data->q_prompt = 1;
	if (!data->here_stock)
		data->here_stock = ft_strnew(BUFF_SHELL);
	stock = ft_strdup(data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	add_to_here_stock('\\', data);
	add_to_here_stock('n', data);
	data->pos = 0;
	ft_putchar('\n');
	quotes_loop(data);
	free(data->lex_str);
	data->lex_str = ft_strdup(data->here_stock);
	data->lex_str = ft_strjoin_free(stock, data->lex_str, 2);
	ft_strdel(&data->here_stock);
	rm_char(&data->lex_str[index], '\'');
	data->q_prompt = 0;
}

void	quotes_loop(t_var *data)
{
	char buffer[6];

	while (1)
	{
		init_subshells(data, buffer);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
			display_subshells(data, buffer);
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
		{
			data->here_stock = ft_strjoin_free(data->here_stock
					, data->lex_str, 0);
			if (data->lex_str[ft_strlen(data->lex_str) - 1] == '\'')
				break ;
			add_to_here_stock('\\', data);
			add_to_here_stock('n', data);
			data->pos = 0;
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
}

void	parse_multi_dquotes(t_var *data, int index)
{
	char *stock;

	data->dq_prompt = 1;
	if (!data->here_stock)
		data->here_stock = ft_strnew(BUFF_SHELL);
	stock = ft_strdup(data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	add_to_here_stock('\\', data);
	add_to_here_stock('n', data);
	data->pos = 0;
	ft_putchar('\n');
	dquotes_loop(data);
	free(data->lex_str);
	data->lex_str = ft_strdup(data->here_stock);
	data->lex_str = ft_strjoin_free(stock, data->lex_str, 2);
	ft_strdel(&data->here_stock);
	rm_char(&data->lex_str[index], '"');
	data->dq_prompt = 0;
}

void	dquotes_loop(t_var *data)
{
	char buffer[6];

	while (1)
	{
		init_subshells(data, buffer);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
			display_subshells(data, buffer);
		if (!ft_strcmp(buffer, (char[4]){ 10, 0, 0, 0}))
		{
			data->here_stock = ft_strjoin_free(data->here_stock
					, data->lex_str, 0);
			if (ft_strchr(data->lex_str, '"'))
				if (!check_backslash(data))
					break ;
			add_to_here_stock('\\', data);
			add_to_here_stock('n', data);
			data->pos = 0;
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
}
