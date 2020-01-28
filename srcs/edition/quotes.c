/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:09:30 by jebrocho          #+#    #+#             */
/*   Updated: 2019/12/14 13:10:07 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void      add_this(char *car, t_var *data)
{
	if (data->pos == data->char_count)
	{
		data->lex_str = ft_strjoin_free(data->lex_str, car, 0);
		data->pos++;
	}
	else
		realloc_str(car[0], data);
}

void read_quotes(t_var *data)
{
	char buffer[6];

	prompt(data);
	while (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	{
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
		{
			ft_putchar(buffer[0]);
			add_this(buffer, data);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
			if (check_quotes(data) == 1)
					prompt(data);
		get_key(data, buffer);
	}
}

static char *quotes_constructor(char *str)
{
	ft_putchar('\n');
	str = ft_strjoin_free(str, "\n", 0);
	return (str);
}

static int 		reset_or_construct(t_var *data, int mod)
{
	if (mod == 0)
	{
		data->lex_str = quotes_constructor(data->lex_str);
		data->pos++;
		data->char_count++;
		return (1);
	}
	else
	{
		data->mod_quotes = 0;
		data->quotes = 0;
		data->dquotes = 0;
		return (0);
	}
}

void algo_reader_quotes(t_var *data, int i)
{
	if (data->lex_str[i] == '\"'
			&& (data->mod_quotes == 0 || data->mod_quotes == 'd'))
	{
		data->dquotes++;
		data->mod_quotes = 'd';
	}
	if (data->lex_str[i] == '\''
			&& (data->mod_quotes == 0 || data->mod_quotes == 'q'))
	{
		data->quotes++;
		data->mod_quotes = 'q';
	}
}

int 		check_quotes(t_var *data)
{
	static int i;
	int 			 r;

	while (data->lex_str[i])
	{
		algo_reader_quotes(data, i);
		if ((data->dquotes > 0 && data->dquotes % 2 == 0)
			|| (data->quotes > 0 && data->quotes % 2 == 0))
		{
			data->quotes = 0;
			data->dquotes = 0;
			data->mod_quotes = 0;
		}
		i++;
	}
	r = (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	 		? reset_or_construct(data, 0) : reset_or_construct(data, 1);
	if (r == 0)
		i = 0;
	return (r);
}
