/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:06:09 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/19 11:19:23 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	move_left(t_var *data)
{
	if (data->pos == 0)
		return ;
	if (data->right == 1)
	{
		abort_selection(data);
		data->in_selection = 0;
	}
	data->pos--;
	TERMCAP("le");
	if (data->in_selection == 1)
	{
		data->left = 1;
		select_mode(data);
	}
	prompt(data);
}

void	move_right(t_var *data)
{
	if (data->pos == ft_strlen(data->lex_str))
		return ;
	if (data->left == 1)
	{
		abort_selection(data);
		data->in_selection = 0;
	}
	data->pos++;
	TERMCAP("nd");
	if (data->in_selection == 1)
	{
		data->right = 1;
		select_mode(data);
	}
	prompt(data);
}

void	move_up(t_var *data)
{
	if (data->pos < data->nb_cols)
		return ;
	if (data->pos - data->nb_cols > 8)
		data->pos -= wind.ws_col;
	else
		data->pos = 0;
	prompt(data);
}

void	move_down(t_var *data)
{
	if (ft_strlen(data->lex_str) <= data->nb_cols
			|| data->pos == ft_strlen(data->lex_str))
		return ;
	if (data->pos + wind.ws_col <= ft_strlen(data->lex_str))
		data->pos += wind.ws_col;
	else
		data->pos = ft_strlen(data->lex_str);
	prompt(data);
}
