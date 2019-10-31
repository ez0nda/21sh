/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:21:43 by jebrocho          #+#    #+#             */
/*   Updated: 2019/10/29 15:27:01 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

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
			data->lex_str = ft_strjoin_free(data->lex_str, &buffer[0], 0);
//			add_to_string(buffer[0], data);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			if (check_quotes(data) == 1)
				read_quotes(data);
		}
		get_key(data, buffer);
	}
}

static char *quotes_constructor(char *str)
{
	ft_putchar('\n');
	str = ft_strjoin_free(str, "\n", 0);
	return (str);
}

int 		check_quotes(t_var *data)
{
	static int i;

//	ft_printf("\nquotes : %d, dquotes : %d, mod : %d\n", data->quotes, data->dquotes, data->mod_quotes);
	while (data->lex_str[i])
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
		if ((data->dquotes > 0 && data->dquotes % 2 == 0)
			|| (data->quotes > 0 && data->quotes % 2 == 0))
		{
			data->quotes = 0;
			data->dquotes = 0;
			data->mod_quotes = 0;
		}
		i++;
	}
	if (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	{
		data->lex_str = quotes_constructor(data->lex_str);
		data->char_count++;
		return (1);
	}
	i = 0;
	data->mod_quotes = 0;
	data->quotes = 0;
	data->dquotes = 0;
	return (0);
}
