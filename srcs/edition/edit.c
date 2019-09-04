/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:36:22 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/04 13:06:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	add_to_string(char c, t_var *data)
{
	if (data->pos == data->char_count)
	{
		data->lex_str[data->pos++] = c;
		data->lex_str[data->pos] = '\0';
	}
	else
		realloc_str(c, data);
}

void	remove_prev_char(t_var *data)
{
	int i;

	i = data->pos - 1;
	if (!data->lex_str[0])
		return ;
	while (data->lex_str[i])
	{
		data->lex_str[i] = data->lex_str[i + 1];
		i++;
	}
	prompt(data);
	if (data->pos > 0)
		data->pos--;
}

void	remove_cur_char(t_var *data)
{
	int i;

	i = data->pos;
	if (!data->lex_str[data->pos])
		return ;
	while (data->lex_str[i])
	{
		data->lex_str[i] = data->lex_str[i + 1];
		i++;
	}
	prompt(data);
}
