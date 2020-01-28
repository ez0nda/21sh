/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 10:47:55 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/24 14:04:49 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	parse_quotes(t_var *data, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strnew(ft_strlen(data->lex_str));
	ft_printf("\nQ - str : |%s|\n", &data->lex_str[index]);
	index++;
	while (data->lex_str[index] && data->lex_str[index] != '\'')
	{
		data->qstr[i] = data->lex_str[index];
		i++;
		index++;
	}
	ft_printf("\nqstr : |%s|\n", data->qstr);
	i = 0;
	while (data->lex_str[i] != '\'')
	{
		tmp[i] = data->lex_str[i];
		i++;
	}
	ft_printf("\ntmp : |%s|\n", tmp);
	data->qstr = ft_strjoin(tmp, data->qstr);
	ft_printf("\ntmp+qstr : |%s| - len : %d\n", data->qstr
			, ft_strlen(data->qstr));
	data->qlen = ft_strlen(data->qstr) + 1;
	data->qstr = ft_strjoin(data->qstr, &data->lex_str[index + 1]);
}

void	parse_dquotes(t_var *data, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	data->qlen = 0;
	tmp = ft_strnew(ft_strlen(data->lex_str));
	ft_printf("\nDQ - str : |%s|\n", &data->lex_str[i]);
	index++;
	while (data->lex_str[index] && data->lex_str[index] != '"')
	{
		data->qstr[i] = data->lex_str[index];
		i++;
		index++;
	}
	ft_printf("\nchar : |%c|\n", data->lex_str[index]);
	if (!data->lex_str[index])
	{
		ft_printf("\nDQUOTES prompt\n");
		return ;
	}
	ft_printf("\nqstr : |%s|\n", data->qstr);
	i = 0;
	while (data->lex_str[i] != '"')
	{
		tmp[i] = data->lex_str[i];
		i++;
	}
	ft_printf("\ntmp : |%s|\n", tmp);
	data->qstr = ft_strjoin(tmp, data->qstr);
	ft_printf("\ntmp+qstr : |%s| - len : %d\n", data->qstr
			, ft_strlen(data->qstr));
	data->qstr = ft_strjoin(data->qstr, &data->lex_str[index + 1]);
}

int		check_quotes(t_var *data)
{
	int i;

	i = 0;
	data->quotes = 0;
	data->dquotes = 0;
	ft_printf("\nstr : |%s|\n", data->lex_str);
	data->qstr = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == '\'')
			data->quotes++;
		if (data->lex_str[i] == '"')
			data->dquotes++;
		i++;
	}
	i = 0;
	ft_printf("\nq : %d - dq : %d\n", data->quotes, data->dquotes);
	if (data->quotes == 0 && data->dquotes == 0)
		return (0);
	while (data->lex_str[i])
	{
		while (data->lex_str[i] != '\'' && data->lex_str[i] != '"')
			i++;
		if (data->lex_str[i] == '\'')
			parse_quotes(data, i);
		else if (data->lex_str[i] == '"')
			parse_dquotes(data, i);
//	if (q % 2 == 0)
//		rm_char(data->lex_str, '"');
//		free(data->lex_str);
		data->lex_str = ft_strdup(data->qstr);
		i = data->qlen;
	}
	ft_printf("\nnewstr : |%s| - index : %d\n", data->lex_str, i);
	ft_printf("\nEND\n", data->lex_str);
	getchar();
	return (0);
}

void	read_quotes(t_var *data)
{}
