/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:21:59 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:06:15 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	add_to_history(t_var *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(data->lex_str);
	if (is_empty(data))
	{
		free(tmp);
		return ;
	}
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
		data->history[0] = ft_strdup(tmp);
	}
	data->new_history = 1;
	free(tmp);
}

void	history_down(t_var *data)
{
	data->hist_pos--;
	if (!data->history[data->hist_pos])
	{
		data->hist_pos++;
		if (data->hist_pos == 0)
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		tputs(tgetstr("cl", NULL), 1, ft_putchar_v2);
		data->pos = ft_strlen(data->lex_str);
		prompt(data);
		return ;
	}
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	data->lex_str = ft_strcpy(data->lex_str, data->history[data->hist_pos]);
}

void	show_history(t_var *data, int mod)
{
	if (data->new_history == 1)
	{
		data->new_history = 0;
		data->hist_pos = 0;
	}
	if (mod == 1)
	{
		if (!data->history[data->hist_pos])
			return ;
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		data->lex_str = ft_strcpy(data->lex_str, data->history[data->hist_pos]);
		data->hist_pos++;
	}
	else
		history_down(data);
	tputs(tgetstr("cl", NULL), 1, ft_putchar_v2);
	data->pos = ft_strlen(data->lex_str);
	prompt(data);
}
