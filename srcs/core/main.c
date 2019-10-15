/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:19:43 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/15 15:25:26 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		exit_shell(t_var *data)
{
	if (tcsetattr(0, TCSANOW, &og_term))
		return (0);
	update_history(data);
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

void	update_history(t_var *data)
{
	t_cmd				*cmd;
	t_redirection_cmd	*rcmd;
	int					new_fd;
	int					back_fd;

	ft_printf("\n-1-\n");
	new_fd = open("/Users/ezonda/.21sh_history", M_WRITE_TRUNC);
	back_fd = dup(0);
	dup2(new_fd, 0);
//	perror("error ");
	ft_printf("\n---\n");
	close(new_fd);
	dup2(back_fd, 0);
	ft_printf("\n-2-\n");


/*	rcmd = malloc(sizeof(*cmd));
	rcmd->type = REDIR;
	rcmd->cmd = cmd;
	rcmd->file = "/Users/ezonda/.21sh_history";
	rcmd->mode = M_WRITE_TRUNC;
	rcmd->fd = 1;
	ft_printf("\n---\n");
	cmd_redir(cmd, data);*/
}

void	get_history(t_var *data, int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**tmp_hist;

	i = 0;
	j = 0;
	line = NULL;
	if (!(tmp_hist = (char**)malloc(sizeof(char*) * BUFF_SHELL)))
		return ;
	while (get_next_line(fd, &line) == 1 && i < BUFF_SHELL)
	{
		tmp_hist[i] = ft_strdup(line);
		i++;
	}
	i--;
	while (i >= 0)
	{
		data->history[j] = ft_strdup(tmp_hist[i]);
		j++;
		i--;
	}
	free_tab(tmp_hist);
}

void	manage_history(t_var *data)
{
	int		fd;
	char	*line;

	fd = open("/Users/ezonda/.21sh_history", O_RDONLY);
	if (fd == -1)
		fd = open("/Users/ezonda/.21sh_history", O_CREAT, S_IRUSR | S_IWUSR);
	else
		get_history(data, fd);
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
	get_input(&data);
	return (exit_shell(&data));
}
