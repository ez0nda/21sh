/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:10:40 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/28 10:48:01 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	parse_multi_quotes(t_var *data, int index)
{
	char buffer[6];
	char *stock;

	data->q_prompt = 1;
	stock = ft_strdup(data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	add_to_here_stock('\\', data);
	add_to_here_stock('n', data);
	ft_putchar('\n');
	while (1)
	{
		get_curs_pos(data, data->pos);
		prompt(data);
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
		{
			ft_putchar(buffer[0]);
			add_to_here_stock(buffer[0], data);
			data->lex_str = ft_strjoin_free(data->lex_str, &buffer[0], 0);
			data->pos = ft_strlen(data->lex_str);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			if (data->lex_str[ft_strlen(data->lex_str) - 1] == '\'')
				break ;
			add_to_here_stock('\\', data);
			add_to_here_stock('n', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
	data->lex_str = ft_strdup(data->here_stock);
	data->lex_str = ft_strjoin(stock, data->here_stock);
	rm_char(&data->lex_str[index], '\'');
	data->q_prompt = 0;
}

int		check_backslah(t_var *data)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
//	ft_printf("\nstr : |%s|\n", data->lex_str);
	while (data->here_stock[i])
	{
		if (data->here_stock[i] == '\\' && data->here_stock[i + 1] == '"')
		{
			ret = 1;
			data->here_stock[i] = data->here_stock[i + 1];
			i++;
		}
		i++;
	}
//	ft_printf("\nRET : %d\n", ret);
	return (ret);
}

void	parse_multi_dquotes(t_var *data, int index)
{
	char buffer[6];
	char *stock;

	data->dq_prompt = 1;
	stock = ft_strdup(data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	add_to_here_stock('\\', data);
	add_to_here_stock('n', data);
	ft_putchar('\n');
	while (1)
	{
		get_curs_pos(data, data->pos);
		prompt(data);
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
		{
			ft_putchar(buffer[0]);
			add_to_here_stock(buffer[0], data);
			data->lex_str = ft_strjoin_free(data->lex_str, &buffer[0], 0);
//			ft_printf("\nstr : |%s|\n", data->lex_str);
			data->pos = ft_strlen(data->lex_str);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
		//	if (data->lex_str[ft_strlen(data->lex_str) - 1] == '"')
		//		break ;
			if (ft_strchr(data->lex_str, '"'))
				if (!check_backslah(data))
				{
//					ft_printf("\nstr : |%s|\n", data->lex_str);
					break ;
				}
			add_to_here_stock('\\', data);
			add_to_here_stock('n', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
//	ft_printf("\nstr : |%s|\n", data->lex_str);
	data->lex_str = ft_strdup(data->here_stock);
//	ft_printf("\nstr : |%s|\n", data->lex_str);
	data->lex_str = ft_strjoin(stock, data->here_stock);
//	ft_printf("\nstr : |%s| - index : %d\n", data->lex_str, index);
	rm_char(&data->lex_str[index], '"');
	data->dq_prompt = 0;
}

void	parse_simple_quotes(t_var *data, int index)
{
	int		i;
	int		last_pos;
	char	*tmp_start;
	char	*tmp_end;

	i = 0;
	tmp_start = ft_strnew(ft_strlen(data->lex_str));
	tmp_end = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i] && data->lex_str[i] != '\'')
	{
		tmp_start[i] = data->lex_str[i];
		i++;
	}
	i = 0;
	index++;
	while (data->lex_str[index] && data->lex_str[index] != '\'')
	{
		data->qstr[i] = data->lex_str[index];
		if (data->qstr[i] == '"')
			data->dquotes--;
		i++;
		index++;
	}
	i = 0;
	index++;
	last_pos = index - 2;
	while (data->lex_str[index])
	{
		tmp_end[i] = data->lex_str[index];
		i++;
		index++;
	}
	data->lex_str = ft_strjoin(tmp_start, data->qstr);
	data->lex_str = ft_strjoin(data->lex_str, tmp_end);
	free(data->qstr);
	data->quotes -= 2;
	read_quotes(data, last_pos);
}

void	parse_simple_dquotes(t_var *data, int index)
{
	int		i;
	int		last_pos;
	char	*tmp_start;
	char	*tmp_end;

	i = 0;
	tmp_start = ft_strnew(ft_strlen(data->lex_str));
	tmp_end = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i] && data->lex_str[i] != '"')
	{
		tmp_start[i] = data->lex_str[i];
		i++;
	}
	i = 0;
	index++;
	while (data->lex_str[index] && data->lex_str[index] != '"')
	{
		if (data->lex_str[index] == '\\' && data->lex_str[index + 1] == '"')
		{
		//	index++;
			last_pos = index;
			while (data->lex_str[index])
			{
				data->lex_str[index] = data->lex_str[index + 1];
				index++;
			}
			index = last_pos;
			data->dquotes--;
		}
		data->qstr[i] = data->lex_str[index];
		if (data->qstr[i] == '\'')
			data->quotes--;
		i++;
		index++;
	}
	i = 0;
	index++;
//	last_pos = index - ft_strlen(data->qstr);	// -2
	last_pos = index - 2;
	while (data->lex_str[index])
	{
		tmp_end[i] = data->lex_str[index];
		i++;
		index++;
	}
//	ft_printf("\nqstr : |%s|\n", data->qstr);
//	ft_printf("\nstart : |%s|\n", tmp_start);
//	ft_printf("\nend : |%s|\n", tmp_end);
//	ft_printf("\nstr : |%s|\n", data->lex_str);
	data->lex_str = ft_strjoin(tmp_start, data->qstr);
//	ft_printf("\nstr : |%s|\n", data->lex_str);
	data->lex_str = ft_strjoin(data->lex_str, tmp_end);
	free(data->qstr);
	data->dquotes -= 2;
//	ft_printf("\nlast_pos : %d\n", last_pos);
//	ft_printf("\nstr : |%s|\n", data->lex_str);
//	ft_printf("\nstr[lp] : |%s|\n", &data->lex_str[last_pos]);
	read_quotes(data, last_pos);
}

int		check_quotes(t_var *data)
{
	int i;

	i = 0;
	data->quotes = 0;
	data->dquotes = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == '\'')
			data->quotes++;
		if (data->lex_str[i] == '"')
			data->dquotes++;
		i++;
	}
	if (data->quotes == 0 && data->dquotes == 0)
		return (0);
	else
		return (1);
}

void	read_quotes(t_var *data, int i)
{
	data->qstr = ft_strnew(ft_strlen(data->lex_str));
//	ft_printf("\nQ : %d - DQ : %d\n", data->quotes, data->dquotes);
	if (!data->lex_str[i])
	{
//		ft_printf("\nRETURN\n");
		return ;
	}
	while (data->lex_str[i]
			&& data->lex_str[i] != '\'' && data->lex_str[i] != '"')
		i++;
//	ft_printf("\nnbdquotes : %d\n", data->dquotes);
	if (data->lex_str[i] == '\'' && data->quotes == 1)
		parse_multi_quotes(data, i);
	else if (data->lex_str[i] == '\'' && data->quotes != 0)
		parse_simple_quotes(data, i);
	else if (data->lex_str[i] == '"' && data->dquotes == 1)
		parse_multi_dquotes(data, i);
	else if (data->lex_str[i] && data->dquotes != 0)
		parse_simple_dquotes(data, i);
}
