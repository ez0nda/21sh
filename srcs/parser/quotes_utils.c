/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:14:19 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 12:38:58 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	add_this(char *car, t_var *data)
{
	if (data->pos == data->char_count)
	{
		data->lex_str = ft_strjoin_free(data->lex_str, car, 0);
		data->pos++;
	}
	else
		realloc_str(car[0], data);
}

void	check_backslash(t_var *data)
{
	int i;
	int deca;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == '\\' && data->lex_str[i + 1] == '"')
		{
			deca = i - 1;
			while (data->lex_str[++deca])
				data->lex_str[deca] = data->lex_str[deca + 1];
			data->lex_str[deca] = '\0';
		}
		i++;
	}
}

void	realloc_quotes(t_var *data, char *start, char *end, int last_pos)
{
	free(data->lex_str);
	data->lex_str = ft_strjoin_free(start, data->qstr, 2);
	data->qstr = ft_strdup(data->lex_str);
	free(data->lex_str);
	data->lex_str = ft_strjoin_free(data->qstr, end, 2);
	read_quotes(data, last_pos);
}

int		get_close_dquotes(t_var *data, int index)
{
	int i;
	int last_pos;

	i = 0;
	while (data->lex_str[index] && data->lex_str[index] != '"')
	{
		if (data->lex_str[index] == '\\' && data->lex_str[index + 1] == '"')
		{
			last_pos = index;
			while (data->lex_str[index])
			{
				data->lex_str[index] = data->lex_str[index + 1];
				index++;
			}
			index = last_pos;
			data->dquotes--;
		}
		data->qstr[i] = data->lex_str[index];
		if (data->qstr[i] == '\'')
			data->quotes--;
		i++;
		index++;
	}
	index++;
	return (index);
}

int		get_close_quotes(t_var *data, int index)
{
	int i;

	i = 0;
	while (data->lex_str[index] && data->lex_str[index] != '\'')
	{
		data->qstr[i] = data->lex_str[index];
		if (data->qstr[i] == '"')
			data->dquotes--;
		i++;
		index++;
	}
	index++;
	return (index);
}
