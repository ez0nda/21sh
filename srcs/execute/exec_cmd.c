/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:44:52 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/10 13:35:31 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void		execute(char **bin_path, pid_t pid, t_var *data)
{
	int		i;
	char	*path;

	i = 0;
	if (bin_path != NULL)
	{
		while (bin_path[i])
		{
			if (data->cmds[0][0] != '/' && data->cmds[0][0] != '.')
				path = init_path(bin_path[i], data->cmds[0]);
			else
				path = ft_strdup(data->cmds[0]);
			if (access(path, X_OK) != -1 && pid == 0)
				execve(path, data->cmds, data->environ);
			free(path);
			i++;
		}
	}
	else
	{
		if (access(data->cmds[0], X_OK) != -1 && pid == 0)
			execve(data->cmds[0], data->cmds, data->environ);
	}
}

void			exec_cmd(char **bin_path, char *cmd, t_var *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	data->cmds = ft_strsplit_ws(cmd);
	while (data->cmds[i])
	{
		if (data->cmds[i][0] == '$')
			data->cmds[i] = get_dollar_var(data->cmds[i], data);
		i++;
	}
	pid = fork();
	execute(bin_path, pid, data);
	if (pid == 0)
	{
		if (data->cmds[0][0] != '\n')
			error_msg(bin_path, data->cmds[0]);
		exit(1);
	}
	if (pid > 0)
		wait(NULL);
}
