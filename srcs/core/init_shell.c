/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:09:03 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 14:16:20 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

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

char	*get_login(char *path)
{
	int		i;
	int		j;
	int		count;
	char	*login;

	i = 0;
	j = 0;
	count = 0;
	login = ft_strnew(sizeof(path));
	while (path[i] && count < 2)
	{
		if (path[i] == '/')
			count++;
		i++;
	}
	while (path[i] && path[i] != '/')
	{
		login[j] = path[i];
		j++;
		i++;
	}
	return (login);
}

void	set_env(t_var *data)
{
	char *path;
	char *login;
	char cwd[256];

	path = getcwd(cwd, sizeof(cwd));
	login = get_login(path);
	if (!(data->environ = (char**)malloc(sizeof(char*) * 6)))
		return ;
	data->environ[0] = ft_strdup("SHLVL=1");
	data->environ[1] = ft_strdup("TERM=xterm-256color");
	data->environ[2] = ft_strjoin("PWD=", path);
	data->environ[3] = ft_strdup("_=/usr/bin/env");
	data->environ[4] = ft_strjoin_free("HOME=/Users/", login, 1);
	data->environ[5] = NULL;
}

void	exit_free(t_var *data)
{
	if (data->environ)
		free_tab(data->environ);
	if (data->home)
		free(data->home);
	if (data->lex_str)
		free(data->lex_str);
	if (data->selection)
		free(data->selection);
	if (data->stock)
		free(data->stock);
	if (data->herend)
		free(data->herend);
	if (data->here_stock)
		free(data->here_stock);
	if (data->files)
		free(data->files);
	if (data->qstr)
		free(data->qstr);
	if (data->tab)
		free(data->tab);
}

int		exit_shell(t_var *data)
{
	if (tcsetattr(0, TCSANOW, &og_term))
		return (0);
	update_history(data);
	free_tab(data->history);
	exit_free(data);
	ft_putendl_fd("exit", 2);
	exit(0);
}
