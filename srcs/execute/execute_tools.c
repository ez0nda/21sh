/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exexute_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:50:13 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/26 14:52:49 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

char	*init_path(char *str, char *cmd)
{
	char *path;
	char *tmp;

	tmp = ft_strjoin(str, "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

void	error_msg(char **bin_path, char *path)
{
	size_t			i;
	char			*abs_path;
	struct stat		st;

	i = 0;
	while (bin_path && bin_path[i])
	{
		abs_path = init_path(bin_path[i], path);
		if (access(abs_path, F_OK) != -1 || access(path, F_OK) != -1)
		{
			lstat(abs_path, &st);
			lstat(path, &st);
			if (S_ISDIR(st.st_mode))
				break ;
			ft_putstr_fd("21sh: permission denied: ", 2);
			ft_putendl_fd(path, 2);
			return ;
		}
		free(abs_path);
		i++;
	}
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putendl_fd(path, 2);
}

int		free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
	return (0);
}

char	*get_dollar_var(char *cmd, t_var *data)
{
	char	*var;

	var = ft_strjoin(&cmd[1], "=");
	if (!get_var(var, data->environ))
	{
		free(var);
		return (cmd);
	}
	cmd = ft_strdup(get_var(var, data->environ));
	free(var);
	return (cmd);
}

char	*get_var(char *str, char **env)
{
	int		i;
	char	cwd[255];
	char	*content;

	i = 0;
	content = NULL;
	while (env[i])
	{
		if (ft_strstr(env[i], str) != NULL && env[i][0] == str[0])
		{
			content = ft_strchr(env[i], '/');
			return (content);
		}
		i++;
	}
	if (!ft_strcmp(str, "PWD=") || !ft_strcmp(str, "OLDPWD="))
		return (getcwd(cwd, sizeof(cwd)));
	return (content);
}
