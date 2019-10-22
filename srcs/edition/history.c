/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:21:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/22 13:03:00 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	add_to_history(t_var *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(data->lex_str);
	while (is_whitespaces(data->lex_str[i]))
		i++;
	if (i == ft_strlen(data->lex_str))
		return;
	i = 0;
	if (!data->history[0])
		data->history[i] = ft_strdup(data->lex_str);
	else
	{
		i = ft_tablen(data->history);
		while (i > 0)
		{
			data->history[i] = data->history[i - 1];
			i--;
		}
		data->history[0] = tmp;
	}
	data->new_history = 1;
}

void	show_history(t_var *data, int mod)
{
	static int i;

	if (data->new_history == 1)
	{
		data->new_history = 0;
		i = 0;
	}
	if (mod == 1)
	{
		if (!data->history[i])
			return ;
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		data->lex_str = ft_strcpy(data->lex_str, data->history[i]);
		i++;
	}
	else
	{
		i--;
		if (!data->history[i])
		{
			i++;
			return ;
		}
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		data->lex_str = ft_strcpy(data->lex_str, data->history[i]);
	}
	data->pos = ft_strlen(data->lex_str);
	prompt(data);
}
