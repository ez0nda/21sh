/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:51:48 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 13:10:02 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	old_pwd(char *old, t_var *data)
{
	char **cmd;

	if (!(cmd = (char**)malloc(sizeof(char*) * 3)))
		return ;
	cmd[0] = ft_strdup("setenv");
	cmd[1] = ft_strjoin("OLDPWD=", old);
	cmd[2] = 0;
	setenv_builtin(data, cmd);
}

void	new_env(t_var *data, char *newp)
{
	char	**cmd;
	char	*old;

	old = get_env(data->environ, "PWD=");
	if (!(cmd = (char**)malloc(sizeof(char*) * 3)))
		return ;
	cmd[0] = ft_strdup("setenv");
	cmd[1] = ft_strjoin("PWD=", newp);
	cmd[2] = 0;
	setenv_builtin(data, cmd);
	old_pwd(old, data);
	free(old);
}

char	*error_cd(char *str, int mod)
{
	if (mod == 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (mod == 1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (mod == 2)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	free(str);
	return (0);
}
