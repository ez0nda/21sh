/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_excute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:55:06 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/24 12:39:27 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int		is_builtin(t_var *data, char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
	{
		exit_shell(data);
//		tcsetattr(0, TCSANOW, &og_term);
//		exit(cmd[1] ? ft_atoi(cmd[1]) : 0);
	}
	else if (!ft_strcmp(cmd[0], "cd"))
		return (cd_builtin(data, cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		return (env_builtin(data->environ));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echo_builtin(cmd));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (setenv_builtin(data, cmd));
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (unsetenv_builtin(data, cmd));
	return (0);
}

int		check_exe(t_var *data, char *cmd)
{
	int		i;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_strsplit_ws(cmd);
	while (split_cmd[i])
	{
		if (split_cmd[i][0] == '$')
			split_cmd[i] = get_dollar_var(split_cmd[i], data);
		i++;
	}
	if (is_builtin(data, split_cmd))
		return (1);
	return (0);
}

void	init_exec(t_var *data)
{
	char	*path;
	char	**bin_path;
	char	**cmds;

	path = get_var("PATH=", data->environ);
	bin_path = ft_strsplit(path, ':');
//	ft_printf("CMDINDEX : %d\n", data->cmd_index);
	if (data->cmd_index == 0)
		ft_putchar_fd('\n', 0);
	if (!check_exe(data, data->cmds[data->cmd_index]))
	{
		exec_cmd(bin_path, data);
	}
}
