/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:10:17 by ezonda            #+#    #+#             */
/*   Updated: 2019/11/23 19:42:03 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static int	remove_var(t_var *data, int index)
{
	char	*home_tmp;
	char	**tmp;

	home_tmp = ft_strdup(get_var("HOME=", data->environ));
	free(data->environ[index]);
	while (data->environ[index])
	{
		data->environ[index] = data->environ[index + 1];
		index++;
	}
	tmp = ft_tabdup(data->environ, 0);
	free_tab(data->environ);
	data->environ = ft_tabdup(tmp, 0);
	free_tab(tmp);
//	data->home = ft_strcpy(data->home, home_tmp);
	free(home_tmp);
	return (1);
}

int			unsetenv_builtin(t_var *data, char **cmd)
{
	int		i;
	char	*to_find;

	i = 0;
	if (!cmd[1])
		return (1);
	to_find = ft_strjoin(cmd[1], "=");
	while (data->environ[i])
	{
		if ((ft_strstr(data->environ[i], to_find) != NULL)
				&& to_find[0] == data->environ[i][0])
		{
			free(to_find);
			free_tab(cmd);
			return (remove_var(data, i));
		}
		i++;
	}
	free(to_find);
	free_tab(cmd);
	return (1);
}
