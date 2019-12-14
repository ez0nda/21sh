/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:44:52 by ezonda            #+#    #+#             */
/*   Updated: 2019/12/14 09:55:26 by ezonda           ###   ########.fr       */
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
			if (data->argv[0][0] != '/' && data->argv[0][0] != '.')
				path = init_path(bin_path[i], data->argv[0]);
			else
				path = ft_strdup(data->argv[0]);
			if (access(path, X_OK) != -1 && pid == 0)
				execve(path, data->argv, data->environ);
			free(path);
			i++;
		}
	}
	else
	{
		if (access(data->argv[0], X_OK) != -1 && pid == 0)
			execve(data->argv[0], data->argv, data->environ);
	}
}

void			exec_cmd(char **bin_path, t_var *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (data->argv[i])
	{
		if (data->argv[i][0] == '$')
			data->argv[i] = get_dollar_var(data->argv[i], data);
		i++;
	}
	pid = fork();
	execute(bin_path, pid, data);
	if (pid == 0)
	{
		if (data->argv[0][0] != '\n')
			error_msg(bin_path, data->argv[0]);
		exit(1);
	}
	if (pid > 0)
		wait(NULL);
}
