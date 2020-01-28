/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:19:43 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/23 16:21:33 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		exit_shell(t_var *data)
{
	if (tcsetattr(0, TCSANOW, &og_term))
		return (0);
	update_history(data);
	free_tab(data->history);
	ft_putendl_fd("exit", 2);
	exit(0);
}

t_var	*update_data(int mod, t_var *data)
{
	static t_var *data2;

	if (mod == 0)
		data2 = data;
	return (data2);
}

void	set_termcanon(t_var *data)
{
	char buffer[256];

	if (tgetent(buffer, get_var("TERM=", data->environ)) <= 0)
		return ;
	if (tcgetattr(0, &og_term) == -1)
		return ;
	term = og_term;
	term.c_lflag &= (~(ICANON | ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
}

void	set_env(t_var *data)
{
	char *path;
	char cwd[256];

	path = getcwd(cwd, sizeof(cwd));
	if (!(data->environ = (char**)malloc(sizeof(char*) * 5)))
		return ;
	data->environ[0] = ft_strdup("SHLVL=1");
	data->environ[1] = ft_strdup("TERM=xterm-256color");
	data->environ[2] = ft_strjoin("PWD=", path);
	data->environ[3] = ft_strdup("_=/usr/bin/env");
	data->environ[4] = NULL;
}

void	update_history(t_var *data)
{
	int		i;
	int		hist;
	int		back_fd;
	char	*str;

	i = 0;
	str = ft_strjoin(getenv("HOME"), "/.21sh_history");
	hist = open(str, O_WRONLY, O_APPEND);
	if (hist == -1)
		return ;
	back_fd = dup(1);
	dup2(hist, 1);
	while (data->history[i])
		ft_putendl(data->history[i++]);
	close(hist);
	dup2(back_fd, 1);
}

void	get_history(t_var *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (get_next_line(fd, &line) == 1 && i < BUFF_SHELL)
	{
		data->history[i] = ft_strdup(line);
		free(line);
		i++;
	}
}

void	manage_history(t_var *data)
{
	int		fd;
	char	*str;

	str = ft_strjoin(getenv("HOME"), "/.21sh_history");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		fd = open(str, O_CREAT, S_IRUSR | S_IWUSR);
	else
		get_history(data, fd);
	free(str);
}

int		main(int ac, char **av, char **env)
{
	t_var data;

	if (!env || !*env)
		set_env(&data);
	else
		data.environ = ft_tabdup(env, 0);
	signal_handler();
	init_shell(&data);
	manage_history(&data);
	set_termcanon(&data);
	if (ac == 1 && av[0] != NULL)
		get_input(&data);
	else
		ft_putendl_fd("21sh: too many arguments\nusage: ./21sh", 2);
	return (exit_shell(&data));
}
