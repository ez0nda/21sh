/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:12:15 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/06 15:08:15 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void			select_mode(t_var *data)
{
	int i;

	i = 0;
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
//	ft_printf("- selection : %s - - pos : %c", data->selection, data->lex_str[data->pos]);
}

void			copy_cut_mode(t_var *data, int mod)
{
	int i;

	i = 0;
	while (i <= ft_strlen(data->lex_str))
	{
		data->tab[i] = 0;
		i++;
	}
	data->in_selection = 0;
	prompt(data);
}

void			paste_mode(t_var *data)
{
	int		i;

	i = 0;
	while (data->selection[i])
	{
		realloc_str(data->selection[i], data);
		i++;
	}
	prompt(data);
}

static void		get_key(t_var *data, char *buffer)
{
	if (!ft_strcmp(buffer, KEY_L))
		move_left(data);
	if (!ft_strcmp(buffer, KEY_R))
		move_right(data);
	if (!ft_strcmp(buffer, KEY_U))
		show_history(data, 1);
	if (!ft_strcmp(buffer, KEY_D))
		show_history(data, 2);
	if (!ft_strcmp(buffer, OPT_L))
		jump(data, 1);
	if (!ft_strcmp(buffer, OPT_R))
		jump(data, 2);
	if (!ft_strcmp(buffer, OPT_U))
		move_up(data);
	if (!ft_strcmp(buffer, OPT_D))
		move_down(data);
	if (!ft_strcmp(buffer, DEL))
		remove_cur_char(data);
	if (!ft_strcmp(buffer, UNDO))
		remove_prev_char(data);
	if (!ft_strcmp(buffer, HOME))
		move_first_last(data, 1);
	if (!ft_strcmp(buffer, END))
		move_first_last(data, 2);
	if (!ft_strcmp(buffer, OPT_S))
		select_mode(data);
	if (!ft_strcmp(buffer, OPT_C))
		copy_cut_mode(data, 0);
	if (!ft_strcmp(buffer, OPT_X))
		copy_cut_mode(data, 1);
	if (!ft_strcmp(buffer, OPT_V))
		paste_mode(data);
}

void			get_input(t_var *data)
{
	char buffer[6];

	ft_putstr("21sh $> ");
	while (1)
	{
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
				|| (buffer[0] == 9 && buffer[1] == 0))
		{
			ft_putchar(buffer[0]);
			add_to_string(buffer[0], data);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			add_to_history(data);
			data->pos = 0;
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_printf("\n21sh $> ");
		}
		get_key(data, buffer);
	}
}
