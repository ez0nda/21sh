/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:47:01 by ezonda            #+#    #+#             */
/*   Updated: 2019/11/08 11:30:38 by ezonda           ###   ########.fr       */
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
			TERMCAP("mr");
			ft_putchar(data->lex_str[i]);
			TERMCAP("me");
		}
		i++;
	}
}

static void		print_prompt(t_var *data)
{
	TERMCAP("md");
	if (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	{
		data->std_prompt = 0;
		ft_putstr("quotes> ");
	}
	else if (data->p_prompt == 1)
		ft_putstr("pipe> ");
	else if (data->h_prompt == 1)
		ft_putstr("heredoc> ");
	else
	{
		data->std_prompt = 1;
		ft_putstr("21sh $> ");
	}
	TERMCAP("me");
}

void			prompt(t_var *data)
{
	int tmp;

	tmp = data->pos;
	if (data->p_prompt != 1)
		data->pos = -9;
	else if (data->p_prompt == 1)
		data->pos = -7;
	else if (data->h_prompt == 1)
		data->pos = -10;
	get_curs_pos(data, data->pos);
	TERMCAP("cd");
//	ft_printf("ret: %d\n", tputs(tgetstr("cd", NULL), 1, ft_putchar_v2));
	print_prompt(data);
	if (data->quotes % 2 == 0 && data->dquotes % 2 == 0)
		print_str(data);
	data->pos = tmp;
	get_curs_pos(data, data->pos);
//	ft_printf("-- pos : %d\n", data->pos);
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
		TERMCAP("le");
		index--;
	}
}
