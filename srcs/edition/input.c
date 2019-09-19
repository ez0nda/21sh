/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:12:15 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/19 11:21:12 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int			check_overflow(t_var *data)
{
	if (data->char_count >= BUFF_SHELL)
	{
		ft_putendl_fd("\nBUFFER OVERFLOW", 2);
		data->pos = 0;
		data->char_count = 0;
		ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		prompt(data);
		return (0);
	}
	return (1);
}

static void		get_copy_paste(t_var *data, char *buffer)
{
	if (!ft_strcmp(buffer, OPT_S))
		select_mode(data);
	if (!ft_strcmp(buffer, OPT_C))
		copy_cut_mode(data, 0);
	if (!ft_strcmp(buffer, OPT_X))
		copy_cut_mode(data, 1);
	if (!ft_strcmp(buffer, OPT_V))
		paste_mode(data);
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
	get_copy_paste(data, buffer);
}
/*
void			odd_quotes(t_var *data)
{
	char buffer[6];
	ft_putstr("\n");
	add_to_string('\n', data);
	ft_putstr("quote>");
	read(0, buffer, sizeof(buffer));
	ft_putchar(buffer[0]);
}
*/
void			remove_quotes(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == 39 || data->lex_str[i] == 34)
		{
			while (data->lex_str[i])
			{
				data->lex_str[i] = data->lex_str[i + 1];
				i++;
			}
			i = 0;
		}
		i++;
	}
}

void			parse_quotes(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == 39)
			data->quotes++;
		else if (data->lex_str[i] == 34)
			data->dquotes++;
		i++;
	}
	if (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	{
		ft_putchar('\n');
		data->std_prompt = 0;
	}
	else
	{
		data->std_prompt = 1;
	}
}

void			stock_str(t_var *data)
{
	int		i;
	int		mod;
	char	*tmp;

	i = 0;
	mod = 1;
	if (!data->stock[0])
	{
		mod = 0;
		data->stock = ft_strdup(data->lex_str);
		while (data->stock[i])
			i++;
		data->stock[i++] = '\n';
		data->stock[i] = '\0';
	}
	while (data->stock[i])
		i++;
	data->stock[i++] = '\n';
	data->stock[i] = '\0';
	data->stock = ft_strjoin(data->stock, data->lex_str);
}

void			get_input(t_var *data)
{
	char buffer[6];

	prompt(data);
	while (1)
	{
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
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
			data->lexer = lexer(data->lex_str);
//			parse_quotes(data);
//			if (data->std_prompt)
//			{
//				if (data->stock[0])
//					data->lex_str = ft_strcpy(data->lex_str, data->stock);
//				remove_quotes(data);
//				data->lexer = lexer(data->lex_str);
//               permet l'exec mais fausse les cas d'erreur
				init_exec(data);
//				ft_bzero(data->stock, ft_strlen(data->stock));
//			}
//			else
//			{
//				stock_str(data);
//			}
			data->pos = 0;
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			prompt(data);
		}
		get_key(data, buffer);
	}
}
