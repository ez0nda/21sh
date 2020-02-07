/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:57:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:00:16 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void		check_single_pipes(t_var *data)
{
	int i;
	int len;
	int last_cmd;

	i = 0;
	len = 0;
	last_cmd = ft_tablen(data->cmds) - 1;
	while (i <= last_cmd)
	{
		last_cmd = ft_tablen(data->cmds) - 1;
		len = ft_strlen(data->cmds[i]);
		while (is_whitespaces(data->cmds[i][len]))
			len--;
		if (data->cmds[i][len - 1] == '|' && i != last_cmd)
			join_cmds(data, i);
		else
			i++;
	}
	if (data->cmds[last_cmd] && data->cmds[last_cmd][len - 1] == '|')
	{
		ft_putchar('\n');
		pipe_prompt(data, last_cmd);
	}
}

void		check_first_last_char(t_var *data, int mod)
{
	int len;

	len = ft_strlen(data->lex_str) - 1;
	if (data->lex_str[0] == '{' && (data->lex_str[1] == '\0' || is_whitespaces(data->lex_str[1])) && mod == 0)
	{
		ft_putchar('\n');
		cursh_prompt(data);
	}
	if (data->lex_str[len] == 92 && mod == 1)
	{
		ft_putchar('\n');
		new_prompt(data);
	}
}

int			parse_error_pipe(t_var *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->lex_str[i] != '|' && data->lex_str[i] != ';'
				&& data->lex_str[i] != ' ' && data->lex_str[i] != '\\'
				&& data->lex_str[i])
		i++;
	j = i;
	while ((data->lex_str[i] == '|' || data->lex_str[i] == ';'
			|| data->lex_str[i] == ' ' || data->lex_str[i] == '\\') && data->lex_str[i])
		i++;
	if (i - 2 == j || data->lex_str[i - 1] == ' ' || i == j)
		return (0);
	if (i == ft_strlen(data->lex_str))
	{
		ft_putstr_fd("\n21sh: parse error near `", 2);
		ft_putchar_fd(data->lex_str[0], 2);
		ft_putchar_fd(data->lex_str[1], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

void		get_copy_paste(t_var *data, char *buffer)
{
	if (!ft_strcmp(buffer, (char[4]){ 127, 0, 0, 0})
			|| !ft_strcmp(buffer, (char[4]){ 8, 0, 0, 0}))
		remove_prev_char(data);
	if (!ft_strcmp(buffer, (char[4]){ -61, -97, 0, 0}))
		select_mode(data);
	if (!ft_strcmp(buffer, (char[4]){ -61, -89, 0, 0}))
		copy_cut_mode(data, 0);
	if (!ft_strcmp(buffer, (char[4]){ -30, -119, -120, 0}))
		copy_cut_mode(data, 1);
	if (!ft_strcmp(buffer, (char[4]){ -30, -120, -102, 0}))
		paste_mode(data);
	if (!ft_strcmp(buffer, (char[4]){ 4, 0, 0, 0}))
	{
		if (data->lex_str[0])
			remove_cur_char(data);
		else
			exit_shell(data);
	}
}

void		get_key(t_var *data, char *buffer)
{
	if (!ft_strcmp(buffer, (char[4]){ 27, 91, 68, 0}))
		move_left(data);
	if (!ft_strcmp(buffer, (char[4]){ 27, 91, 67, 0}))
		move_right(data);
	if (!ft_strcmp(buffer, (char[4]){ 27, 91, 65, 0}))
		show_history(data, 1);
	if (!ft_strcmp(buffer, (char[4]){ 27, 91, 66, 0}))
		show_history(data, 2);
	if (!ft_strcmp(buffer, (char[5]){ 27, 27, 91, 68, 0}))
		jump(data, 1);
	if (!ft_strcmp(buffer, (char[5]){ 27, 27, 91, 67, 0}))
		jump(data, 2);
	if (!ft_strcmp(buffer, (char[5]){ 27, 27, 91, 65, 0}))
		move_up(data);
	if (!ft_strcmp(buffer, (char[5]){ 27, 27, 91, 66, 0}))
		move_down(data);
	if (!ft_strcmp(buffer, (char[5]){ 27, 91, 51, 126, 0}))
		remove_cur_char(data);
	if (!ft_strcmp(buffer, (char[4]){ 27, 91, 72, 0}))
		move_first_last(data, 1);
	if (!ft_strcmp(buffer, (char[4]){ 27, 91, 70, 0}))
		move_first_last(data, 2);
	get_copy_paste(data, buffer);
}
