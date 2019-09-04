/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:06:09 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/04 13:47:42 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	move_left(t_var *data)
{
	if (data->pos == 0)
		return ;
	data->pos--;
	TERMCAP("le");
}

void	move_right(t_var *data)
{
	if (data->pos == ft_strlen(data->lex_str))
		return ;
	data->pos++;
	TERMCAP("nd");
}

void	move_up(t_var *data)
{
	if (data->pos <= data->nb_cols)
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
	prompt(data);
}
