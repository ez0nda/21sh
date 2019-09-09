/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:40:10 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/09 11:38:05 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	move_first_last(t_var *data, int mod)
{
	int tmp;

	if (mod == 1)
	{
		data->pos = 0;
		prompt(data);
	}
	else
	{
		data->pos = ft_strlen(data->lex_str);
		prompt(data);
	}
}

void	get_prev_word(t_var *data)
{
	while ((data->lex_str[data->pos] == ' ' || data->lex_str[data->pos] == '\t')
			&& data->pos > 0)
		data->pos--;
	while ((data->lex_str[data->pos] != ' ' && data->lex_str[data->pos] != '\t')
			&& data->pos > 0)
		data->pos--;
	while ((data->lex_str[data->pos] == ' ' || data->lex_str[data->pos] == '\t')
			&& data->pos > 0)
		data->pos--;
	if (data->pos != 0)
		data->pos++;
	prompt(data);
}

void	get_next_word(t_var *data)
{
	while ((data->lex_str[data->pos] == ' ' || data->lex_str[data->pos] == '\t')
			&& data->pos < ft_strlen(data->lex_str))
		data->pos++;
	while ((data->lex_str[data->pos] != ' ' && data->lex_str[data->pos] != '\t')
			&& data->pos < ft_strlen(data->lex_str))
		data->pos++;
	while ((data->lex_str[data->pos] == ' ' || data->lex_str[data->pos] == '\t')
			&& data->pos < ft_strlen(data->lex_str))
		data->pos++;
	prompt(data);
}

void	jump(t_var *data, int mod)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_strsplit_ws(data->lex_str);
	while (words[i])
		i++;
	if (i <= 1)
		return ;
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	if (mod == 1)
		get_prev_word(data);
	else
		get_next_word(data);
}
