/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:36:22 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/06 10:08:55 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void		free_lst(t_list *lst)
{
	t_list *tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}

void	add_to_string(char c, t_var *data)
{
	if (data->pos == data->char_count)
	{
		data->lex_str[data->pos++] = c;
		data->lex_str[data->pos] = '\0';
	}
	else
		realloc_str(c, data);
}

void	realloc_str(char c, t_var *data)
{
	int		i;
	int		j;
	char	s1[BUFF_SHELL];
	char	s2[BUFF_SHELL];

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
	free(data->lex_str);
	data->lex_str = ft_strjoin(s1, s2);
	data->pos++;
	prompt(data);
}

void	remove_prev_char(t_var *data)
{
	int i;

	i = data->pos - 1;
	if (!data->lex_str[0])
		return ;
	while (data->lex_str[i])
	{
		data->lex_str[i] = data->lex_str[i + 1];
		i++;
	}
	if (data->pos > 0)
		data->pos--;
	prompt(data);
	data->char_count--;
}

void	remove_cur_char(t_var *data)
{
	int i;

	i = data->pos;
	if (!data->lex_str[data->pos])
		return ;
	while (data->lex_str[i])
	{
		data->lex_str[i] = data->lex_str[i + 1];
		i++;
	}
	prompt(data);
	data->char_count--;
}
