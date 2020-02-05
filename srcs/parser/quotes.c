/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:10:40 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 12:39:55 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	parse_simple_quotes(t_var *data, int index)
{
	int		i;
	int		last_pos;
	char	*tmp_start;
	char	*tmp_end;

	i = 0;
	tmp_start = ft_strnew(ft_strlen(data->lex_str));
	tmp_end = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i] && data->lex_str[i] != '\'')
	{
		tmp_start[i] = data->lex_str[i];
		i++;
	}
	i = 0;
	index++;
	index = get_close_quotes(data, index);
	last_pos = index - 2;
	while (data->lex_str[index])
	{
		tmp_end[i] = data->lex_str[index];
		i++;
		index++;
	}
	data->quotes -= 2;
	realloc_quotes(data, tmp_start, tmp_end, last_pos);
}

void	parse_simple_dquotes(t_var *data, int index)
{
	int		i;
	int		last_pos;
	char	*tmp_start;
	char	*tmp_end;

	i = 0;
	tmp_start = ft_strnew(ft_strlen(data->lex_str));
	tmp_end = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i] && data->lex_str[i] != '"')
	{
		tmp_start[i] = data->lex_str[i];
		i++;
	}
	i = 0;
	index++;
	index = get_close_dquotes(data, index);
	last_pos = index - 2;
	while (data->lex_str[index])
	{
		tmp_end[i] = data->lex_str[index];
		i++;
		index++;
	}
	data->dquotes -= 2;
	add_exp(data);
	realloc_quotes(data, tmp_start, tmp_end, last_pos);
}

int		check_quotes(t_var *data)
{
	int i;

	i = 0;
	data->quotes = 0;
	data->dquotes = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == '\'')
			data->quotes++;
		if (data->lex_str[i] == '"')
			data->dquotes++;
		i++;
	}
	if (data->quotes == 0 && data->dquotes == 0)
		return (0);
	else
	{
		data->mod_quotes = 1;
		return (1);
	}
}

void	read_quotes(t_var *data, int i)
{
	data->qstr = ft_strnew(ft_strlen(data->lex_str));
	if (!data->lex_str[i])
		return ;
	while (data->lex_str[i]
			&& data->lex_str[i] != '\'' && data->lex_str[i] != '"')
		i++;
	if (data->lex_str[i] == '\'' && data->quotes == 1)
		parse_multi_quotes(data, i, 1);
	else if (data->lex_str[i] == '\'' && data->quotes != 0)
		parse_simple_quotes(data, i);
	else if (data->lex_str[i] == '"' && data->dquotes == 1)
		parse_multi_dquotes(data, i, 1);
	else if (data->lex_str[i] && data->dquotes != 0)
		parse_simple_dquotes(data, i);
	ft_strdel(&data->qstr);
}
