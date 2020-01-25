/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 00:49:56 by jebrocho          #+#    #+#             */
/*   Updated: 2020/02/12 10:57:06 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int		ret_quotes(t_var *data, int quotes, int dquotes, int index)
{
	int		i;

	if (quotes % 2 == 0)
		return (0);
	else if (quotes % 2 == 1 && dquotes == 0)
		return (1);
	else
	{
		i = ft_strlen(data->lex_str);
		dquotes = 0;
		while (data->lex_str[--i] != '\'')
		{
			if (data->lex_str[i] == '"' && dquotes == 0)
				index = i;
			if (data->lex_str[i] == '"')
				dquotes++;
		}
		if (dquotes % 2 == 1)
		{
			data->q_prompt = 0;
			parse_multi_dquotes(data, index, 0);
			data->dq_prompt = 0;
		}
		return (1);
	}
}

int		check_quotes_end(t_var *data)
{
	int		i;
	int		quotes;
	int		dquotes;
	int		index;

	quotes = 0;
	dquotes = 0;
	index = 0;
	i = -1;
	while (data->lex_str[++i])
	{
		if (data->lex_str[i] == '\'')
			quotes++;
		if (data->lex_str[i] == '"')
			dquotes++;
	}
	return (ret_quotes(data, quotes, dquotes, index));
}

int		ret_dquotes(t_var *data, int quotes, int dquotes, int index)
{
	int i;

	if (dquotes % 2 == 0)
		return (0);
	else if (dquotes % 2 == 1 && quotes == 0)
		return (1);
	else
	{
		i = ft_strlen(data->lex_str);
		quotes = 0;
		while (data->lex_str[--i] != '"')
		{
			if (data->lex_str[i] == '\'' && quotes == 0)
				index = i;
			if (data->lex_str[i] == '\'')
				quotes++;
		}
		if (quotes % 2 == 1)
		{
			data->dq_prompt = 0;
			parse_multi_quotes(data, index, 0);
			data->q_prompt = 0;
		}
		return (1);
	}
}

int		check_dquotes_end(t_var *data)
{
	int		i;
	int		quotes;
	int		dquotes;
	int		index;

	quotes = 0;
	dquotes = 0;
	i = -1;
	index = 0;
	while (data->lex_str[++i])
	{
		if (data->lex_str[i] == '\'')
			quotes++;
		if (data->lex_str[i] == '"' && data->lex_str[i - 1] != '\\')
			dquotes++;
	}
	return (ret_dquotes(data, quotes, dquotes, index));
}

void	rm_dquotes(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != '\\')
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
			i = 0;
		}
		i++;
	}
}
