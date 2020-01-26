/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:37:37 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:08:12 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void		print_str(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->tab[i] == 0)
			ft_putchar(data->lex_str[i]);
		else
		{
			tputs(tgetstr("mr", NULL), 1, ft_putchar_v2);
			ft_putchar(data->lex_str[i]);
			tputs(tgetstr("me", NULL), 1, ft_putchar_v2);
		}
		i++;
	}
}

static void		print_prompt(t_var *data)
{
	if (data->q_prompt == 1)
		ft_putstr("quote> ");
	else if (data->dq_prompt == 1)
		ft_putstr("dquote> ");
	else if (data->p_prompt == 1)
		ft_putstr("pipe> ");
	else if (data->h_prompt == 1)
		ft_putstr("heredoc> ");
	else if (data->n_prompt == 1)
		ft_putstr("> ");
	else if (data->c_prompt == 1)
		ft_putstr("cursh> ");
	else
	{
		tputs(tgetstr("md", NULL), 1, ft_putchar_v2);
		data->std_prompt = 1;
		ft_putstr("21sh $> ");
		tputs(tgetstr("me", NULL), 1, ft_putchar_v2);
	}
	print_str(data);
}

void			prompt(t_var *data)
{
	int tmp;

	tmp = data->pos;
	if (!data->lex_str)
		if (!(data->lex_str = ft_strnew(BUFF_SHELL)))
			return ;
	if (data->q_prompt == 1)
		data->pos = -8;
	else if (data->dq_prompt == 1)
		data->pos = -9;
	else if (data->p_prompt != 1)
		data->pos = -9;
	else if (data->p_prompt == 1)
		data->pos = -7;
	else if (data->h_prompt == 1)
		data->pos = -10;
	else if (data->n_prompt == 1)
		data->pos = -3;
	else if (data->c_prompt == 1)
		data->pos = -8;
	get_curs_pos(data, data->pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_v2);
	print_prompt(data);
	data->pos = tmp;
	get_curs_pos(data, data->pos);
}

void			get_winsize(t_var *data)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wind);
	data->nb_cols = wind.ws_col - 8;
	data->nb_rows = wind.ws_row;
}

void			get_curs_pos(t_var *data, int index)
{
	index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar_v2);
		index--;
	}
}
