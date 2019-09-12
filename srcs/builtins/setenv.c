/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:09:04 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/10 15:41:20 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static int	create_var(t_var *data, char **cmd)
{
	int		i;
	char	**tmp;

	i = 0;
	while (data->environ[i])
		i++;
	tmp = ft_tabdup(data->environ, 0);
	free_tab(data->environ);
	data->environ = ft_tabdup(tmp, 1);
	data->environ[i++] = ft_strdup(cmd[1]);
	data->environ[i] = NULL;
	free_tab(tmp);
	free_tab(cmd);
	return (1);
}

static int	replace_var(t_var *data, char **cmd, int index)
{
	int i;

	i = 0;
	free(data->environ[index]);
	data->environ[index] = ft_strdup(cmd[1]);
	free_tab(cmd);
	return (1);
}

int			parse_cmd(char *cmd)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	if (ft_isdigit(cmd[0]))
	{
		while (cmd[i] && cmd[i] != '=')
			i++;
		ft_putstr_fd("setenv: not an identifier: ", 2);
		ft_putendl_fd(ft_strsub(cmd, 0, i), 2);
		return (1);
	}
	if (!ft_strchr(cmd, '='))
		return (1);
	return (0);
}

int			setenv_builtin(t_var *data, char **cmd)
{
	int		i;
	char	*var_name;

	i = 0;
	if (!cmd[1] || parse_cmd(cmd[1]))
	{
		free_tab(cmd);
		return (1);
	}
	while (cmd[1][i] != '=')
		i++;
	var_name = ft_strsub(cmd[1], 0, i + 1);
	while (data->environ[i])
	{
		if (ft_strstr(data->environ[i], var_name) != NULL
				&& data->environ[i][0] == var_name[0])
		{
			free(var_name);
			return (replace_var(data, cmd, i));
		}
		i++;
	}
	free(var_name);
	return (create_var(data, cmd));
}
