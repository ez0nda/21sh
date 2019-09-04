/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:08:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:33:39 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		dispatch(char *buf, t_env *v, char **line, int mod)
{
	free(buf);
	if (mod == 0)
		ft_cd(line, v);
	if (mod == 1)
		ft_setenv(line, v);
	if (mod == 2)
		p_env();
	if (mod == 3)
		ft_unsetenv(line);
	free_tab(line);
	return (1);
}

int				builtin(char *buf, t_env *v)
{
	char **line;

	line = parse_line(buf);
	if (!line)
		return (1);
	if (ft_strcmp(line[0], "exit") == 0)
		line[1] != NULL ? exit(ft_atoi(line[1])) : exit(0);
	if (ft_strcmp(line[0], "cd") == 0)
		return (dispatch(buf, v, line, 0));
	if (ft_strcmp(line[0], "setenv") == 0)
		return (dispatch(buf, v, line, 1));
	if (ft_strcmp(line[0], "env") == 0)
		return (dispatch(buf, v, line, 2));
	if (ft_strcmp(line[0], "unsetenv") == 0)
		return (dispatch(buf, v, line, 3));
	free_tab(line);
	return (0);
}
