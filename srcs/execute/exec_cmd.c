/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:44:52 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/11 12:02:36 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void		execute(char **bin_path, char **cmd, pid_t father, t_var *data)
{
	int		i;
	char	*path;

	i = 0;
	if (bin_path != NULL)
	{
		while (bin_path[i])
		{
			if (cmd[0][0] != '/' && cmd[0][0] != '.')
				path = init_path(bin_path[i], cmd[0]);
			else
				path = ft_strdup(cmd[0]);
			if (access(path, X_OK) != -1 && father == 0)
				execve(path, cmd, data->environ);
			free(path);
			i++;
		}
	}
	else
	{
		if (access(cmd[0], X_OK) != -1 && father == 0)
			execve(cmd[0], cmd, data->environ);
	}
}

void			exec_cmd(char **bin_path, char **lexer, t_var *data)
{
	int		i;
	pid_t	father;

	i = 0;
	while (data->lexer[i])
	{
		if (data->lexer[i][0] == '$')
			data->lexer[i] = get_dollar_var(lexer[i], data);
		i++;
	}
	father = fork();
	execute(bin_path, lexer, father, data);
	if (father == 0)
	{
		if (lexer[0][0] != '\n')
			error_msg(bin_path, lexer[0]);
		exit(1);
	}
	if (father > 0)
		wait(NULL);
//	free_tab(data->lexer);
}

/*void			multi_cmd(char **bin_path, char *buff, t_var *data)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = ft_strsplit(buff, ';');
	while (cmd[i])
	{
//		if (!check_exe(cmd[i], data))
//			exec_cmd(bin_path, cmd[i], data);
		i++;
	}
//	free_tab(cmd);
	//
}*/

/*int				is_builtin(char **cmd, t_var *data)
{
	if (!ft_strcmp(cmd[0], "exit"))
		exit(cmd[1] ? ft_atoi(cmd[1]) : 0);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (cd_builtin(cmd, data));
	else if (!ft_strcmp(cmd[0], "env"))
		return (free_tab(cmd) || env_builtin(data->environ));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echo_builtin(cmd));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (setenv_builtin(data, cmd));
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (unsetenv_builtin(data, cmd));
	free_tab(cmd);
	return (0);
}*/

/*int				check_exe(char *buff, t_var *data)
{
	size_t		i;
	char		**cmd;

	i = 0;
	cmd = NULL;
	while (buff[i] && ft_is_ws(buff[i]))
		i++;
	if (i == ft_strlen(buff))
		return (1);
	cmd = ft_strsplit_ws(buff);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
			cmd[i] = get_dollar_var(cmd[i], data);
		i++;
	}
	if (is_builtin(cmd, data))
		return (1);
	return (0);
}*/
