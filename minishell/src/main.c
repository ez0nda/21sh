/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:35:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:58:31 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pid_error(char **line, char *buf, pid_t pid)
{
	char *path;

	if (pid == 0)
	{
		path = ft_strdup(line[0]);
		if (execve(path, line, g_env) == -1)
		{
			if (access(path, X_OK) == -1 && access(path, F_OK) == 0)
				error_path(1, line[0]);
			else if (access(path, X_OK) == 0)
				error_path(1, line[0]);
		}
	}
	if (pid == 0)
	{
		if (buf[0] != '\n')
			print_error(buf);
		exit(1);
	}
}

int		exec_all(char **exe, char *buf, t_env *v)
{
	pid_t	pid;
	char	**line;
	char	*path;
	int		i;

	i = -1;
	line = parse_line(buf);
	pid = fork();
	if (v->nopath != 1)
	{
		while (exe[++i])
		{
			path = ft_strjoin(exe[i], "/");
			if (line[0])
				path = ft_strjoin_free(path, line[0], 0);
			if (pid == 0)
				execve(path, line, g_env);
			free(path);
		}
	}
	pid_error(line, buf, pid);
	if (pid > 0)
		wait(NULL);
	free(buf);
	return (free_tab(line));
}

char	*get_pwd(void)
{
	char cwd[256];
	char *pwd;

	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (".");
	if (ft_strcmp(pwd, "/") != 0)
	{
		pwd = ft_strrchr(pwd, '/');
		rm_one(pwd, 0);
	}
	return (pwd);
}

int		ft_read(t_env *v)
{
	char *stock;
	char *path;
	char **exe;
	char buf[4096];

	path = get_pwd();
	ft_printf("[%s]-> ", path);
	ft_bzero(buf, 4096);
	if (read(0, &buf, 4096) == -1)
		return (-1);
	stock = rm_whitespace(buf, v);
	if (builtin(stock, v) == 1)
		return (ft_reset(v));
	path = get_env_val(v->path);
	exe = ft_split(path, ':');
	free(path);
	if (line_of_env("PATH") == -1)
		v->nopath = 1;
	exec_all(exe, stock, v);
	free_tab(exe);
	return (ft_reset(v));
}

int		main(int ac, char **av, char **env)
{
	t_env v;

	(void)av;
	(void)ac;
	if (!env[0])
		return (error_env());
	g_env = ft_tabdup(env);
	v.pwd = ft_strdup(g_env[line_of_env("PWD")]);
	v.home = ft_strdup(g_env[line_of_env("HOME")]);
	v.path = ft_strdup(g_env[line_of_env("PATH")]);
	signal(2, ctrl);
	while (ft_read(&v) == 1)
	{
	}
	return (0);
}
