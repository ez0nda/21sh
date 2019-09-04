/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:21:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/06 15:36:46 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		new_path(char *path, t_env *v)
{
	char *tir;

	if (v->istir == 1)
	{
		if (line_of_env("OLDPWD") > -1)
		{
			tir = get_env_val(v->pwd);
			free(v->pwd);
			v->pwd = ft_strdup(g_env[line_of_env("OLDPWD")]);
			change_env(tir, "OLDPWD", v);
			free(tir);
			tir = get_env_val(v->pwd);
			change_env(tir, "PWD", v);
			chdir(tir);
			free(tir);
		}
		else
			ft_printf("cd: OLDPWD not set\n");
		v->istir = 0;
		return (-1);
	}
	free(v->pwd);
	v->pwd = ft_strjoin("PWD=", path);
	return (0);
}

void	did_path(char *s, t_env *v)
{
	char *tmp;

	tmp = get_env("PWD");
	if (line_of_env("OLDPWD") > -1)
		change_env(tmp, "OLDPWD", v);
	else
	{
		tmp = ft_strjoin_free("OLDPWD=", tmp, 1);
		new_env(tmp, v);
	}
	change_env(s, "PWD", v);
	free(s);
	free(tmp);
}

int		check_error(char *path, t_env *v)
{
	DIR		*dir;
	char	*s;

	if (v->istir != 1)
		s = parse_error(path, v);
	if (lstat(s, &st) < 0 && v->istir != 1)
		return (error_cd(s, 0));
	if (ft_is_dir(s) == 0 && v->istir != 1)
		return (error_cd(s, 2));
	dir = opendir(s);
	if (dir == NULL && v->istir != 1)
		return (error_cd(s, 1));
	if (v->istir == 0)
		closedir(dir);
	if (new_path(s, v) == -1)
		return (-1);
	did_path(s, v);
	return (0);
}

void	home(t_env *v)
{
	int		i;
	char	*save;
	char	*freed;

	i = 0;
	save = get_env_val(v->home);
	free(v->pwd);
	v->pwd = ft_strjoin("PWD=", save);
	freed = get_env("PWD");
	if (line_of_env("OLDPWD") > -1)
		change_env(freed, "OLDPWD", v);
	else
	{
		freed = ft_strjoin_free("OLDPWD=", freed, 1);
		new_env(freed, v);
	}
	free(freed);
	change_env(save, "PWD", v);
	free(save);
}

int		ft_cd(char **line, t_env *v)
{
	int		i;
	char	*newp;

	i = 0;
	if (!line[1])
		home(v);
	else
	{
		parse_arg(line[1], '/', v);
		if (check_error(line[1], v) == -1)
			return (1);
	}
	newp = get_env_val(v->pwd);
	chdir(newp);
	free(newp);
	return (1);
}
