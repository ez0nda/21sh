/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:00:50 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/12 11:26:18 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	abort_selection(t_var *data)
{
	int i;

	i = 0;
	ft_bzero(data->selection, ft_strlen(data->lex_str));
	while (i <= ft_strlen(data->lex_str))
	{
		data->tab[i] = 0;
		i++;
	}
	data->left = 0;
	data->right = 0;
	prompt(data);
}

void	select_mode(t_var *data)
{
	int i;

	i = 0;
	if (data->in_selection == 0)
		ft_bzero(data->selection, ft_strlen(data->lex_str));
	data->in_selection = 1;
	while (data->selection[i])
		i++;
	data->selection[i++] = data->lex_str[data->pos];
	data->selection[i] = '\0';
	if (data->tab[data->pos] == 0)
		data->tab[data->pos] = 1;
	else
		data->tab[data->pos] = 0;
	prompt(data);
}

void	copy_cut_mode(t_var *data, int mod)
{
	int i;

	i = 0;
	if (data->in_selection == 0)
		return ;
	if (mod == 1)
	{
		while (data->lex_str[i++])
		{
			if (data->tab[i] == 1)
			{
				remove_cur_char(data);
				data->pos--;
			}
		}
	}
	data->pos++;
	i = 0;
	while (i <= ft_strlen(data->lex_str))
	{
		data->tab[i] = 0;
		i++;
	}
	data->in_selection = 0;
	prompt(data);
}

void	paste_mode(t_var *data)
{
	int		i;

	i = 0;
	data->char_count += ft_strlen(data->selection);
	if (!check_overflow(data))
		return ;
	while (data->selection[i])
	{
		realloc_str(data->selection[i], data);
		i++;
	}
	prompt(data);
}
