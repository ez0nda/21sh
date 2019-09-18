/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_excute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:55:06 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/16 14:23:04 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int		is_builtin(t_var *data)
{
	if (!ft_strcmp(data->lexer[0], "exit"))
		exit(data->lexer[1] ? ft_atoi(data->lexer[1]) : 0);
	else if (!ft_strcmp(data->lexer[0], "cd"))
	{
		ft_putstr("cd\n");
		return (1);
	}
	else if (!ft_strcmp(data->lexer[0], "env"))
		return (env_builtin(data->environ));
/*	else if (!ft_strcmp(data->lexer[0], "echo"))
	{
		ft_putstr("echo\n");
		return (1);
	}*/
	else if (!ft_strcmp(data->lexer[0], "setenv"))
		return (setenv_builtin(data, data->lexer));
	else if (!ft_strcmp(data->lexer[0], "unsetenv"))
		return (unsetenv_builtin(data, data->lexer));
	return (0);
}

int		check_exe(t_var *data)
{
	int i;

	i = 0;
	while (data->lexer[i])
	{
		if (data->lexer[i][0] == '$')
			data->lexer[i] = get_dollar_var(data->lexer[i], data);
		i++;
	}
	if (is_builtin(data))
		return (1);
	return (0);
}

void	init_exec(t_var *data)
{
	char	*path;
	char	**bin_path;

	bin_path = NULL;
	ft_putchar('\n');
	if (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
		return ;
	if (!data->lexer[0])
		return;
	path = get_var("PATH=", data->environ);
	bin_path = ft_strsplit(path, ':');
	if (!check_exe(data))
		exec_cmd(bin_path, data->lexer, data);
}
