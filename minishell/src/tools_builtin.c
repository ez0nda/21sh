/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:26:21 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:43:21 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_last(t_env *v)
{
	int j;

	j = 0;
	while (v->pwd[j])
		j++;
	if (j == 4)
		return ;
	while (v->pwd[j] != '/')
		j--;
	if (j > 4)
		v->pwd[j] = '\0';
	else
		v->pwd[++j] = '\0';
}

void	add_last(char *str, t_env *v)
{
	v->pwd = ft_strjoin_free(v->pwd, "/", 0);
	v->pwd = ft_strjoin_free(v->pwd, str, 0);
}

char	*add_error(char *s, char *new)
{
	s = ft_strjoin_free(s, "/", 0);
	s = ft_strjoin_free(s, new, 0);
	return (s);
}

void	rm_error(char *s)
{
	int j;

	j = 0;
	while (s[j])
		j++;
	if (j == 1)
		return ;
	while (s[j] != '/')
		j--;
	if (j > 1)
		s[j] = '\0';
	else
		s[++j] = '\0';
}

int		ft_reset(t_env *v)
{
	int i;

	v->istir = 0;
	i = line_of_env("PWD");
	if (i > -1)
	{
		free(g_env[i]);
		g_env[i] = ft_strdup(v->pwd);
	}
	i = line_of_env("HOME");
	if (i > -1)
	{
		free(g_env[i]);
		g_env[i] = ft_strdup(v->home);
	}
	i = line_of_env("PATH");
	if (i > -1)
	{
		free(g_env[i]);
		g_env[i] = ft_strdup(v->path);
	}
	return (1);
}
