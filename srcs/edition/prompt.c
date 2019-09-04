/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:47:01 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/04 13:48:25 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	prompt(t_var *data)
{
	int tmp;

	tmp = data->pos;
	data->pos = -9;
	get_curs_pos(data, data->pos);
	TERMCAP("cd");
	ft_putstr("21sh $> ");
	ft_putstr(data->lex_str);
	data->pos = tmp;
	get_curs_pos(data, data->pos);
}

void	realloc_str(char c, t_var *data)
{
	int		i;
	int		j;
	char	s1[BUFF_SIZE];
	char	s2[BUFF_SIZE];

	j = 0;
	i = data->pos;
	while (data->lex_str[i])
		s2[j++] = data->lex_str[i++];
	s2[j] = '\0';
	i = 0;
	j = 0;
	while (i < data->pos)
		s1[j++] = data->lex_str[i++];
	s1[i++] = c;
	s1[i] = '\0';
	data->lex_str = ft_strjoin(s1, s2);
	data->pos++;
	prompt(data);
}

void	get_winsize(t_var *data)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wind);
	data->nb_cols = wind.ws_col - 8;
	data->nb_rows = wind.ws_row;
}

void	get_curs_pos(t_var *data, int index)
{
	index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		TERMCAP("le");
		index--;
	}
}
