/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:21:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/04 13:06:58 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	add_to_history(t_var *data)
{
	int i;
	char *tmp;

	i = 0;
	tmp = ft_strdup(data->lex_str);
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
}

void	show_history(t_var *data, int mod)
{
	static int	i;

	if (mod == 1 && i <= ft_tablen(data->history))
	{
		prompt(data);
		if (i == ft_tablen(data->history))
			return ;
		if (i >= 0)
		{
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			data->lex_str = ft_strcpy(data->lex_str, data->history[i]);
		}
		i++;
	}
	else if (mod == 2 && i >= 0)
	{
		prompt(data);
		if (i < ft_tablen(data->history))
		{
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			data->lex_str = ft_strcpy(data->lex_str, data->history[i]);
		}
		i--;
	}
	data->pos = ft_strlen(data->lex_str);
}
