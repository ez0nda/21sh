/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:19:43 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/14 15:29:38 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		exit_shell(void)
{
	if (tcsetattr(0, TCSANOW, &og_term))
		return (0);
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

	if (tgetent(buffer, getenv("TERM")) <= 0)
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
	if (!(data->environ = (char**)malloc(sizeof(char*) * 4)))
		return ;
	data->environ[0] = ft_strjoin("PWD=", path);
	data->environ[1] = ft_strdup("SHLVL=1");
	data->environ[2] = ft_strdup("_=/usr/bin/env");
	data->environ[3] = NULL;
}

void	create_history(t_var *data)
{
	
}

void	update_history(t_var *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
//		ft_putstr("history : ");
//		ft_putendl(ft_strdup(line));
		data->history[i] = ft_strdup(line);
		ft_printf("history : %s\n", data->history[i]);
//		free(line);
		i++;
	}
}

void	get_history(t_var *data)
{
	int		fd;
	char	*line;

	fd = open("/Users/ezonda/.zsh_history", O_RDONLY);
	if (fd == -1)
		create_history(data);
	else
		update_history(data, fd);
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
	get_history(&data);
	set_termcanon(&data);
	get_input(&data);
	return (exit_shell());
}
