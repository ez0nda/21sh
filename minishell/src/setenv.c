/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:53:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 14:36:08 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				p_env(void)
{
	int i;

	i = -1;
	while (g_env[++i])
		ft_printf("%s\n", g_env[i]);
	return (1);
}

void			new_env(char *l, t_env *v)
{
	char	**stock_env;
	int		i;

	i = 0;
	while (g_env[i])
		i++;
	if (!(stock_env = (char**)malloc(sizeof(char*) * (i + 2))))
		exit(EXIT_FAILURE);
	i = -1;
	while (g_env[++i])
	{
		stock_env[i] = ft_strdup(g_env[i]);
		free(g_env[i]);
	}
	free(g_env);
	stock_env[i] = ft_strdup(l);
	i++;
	stock_env[i] = 0;
	g_env = ft_tabdup(stock_env);
	free_tab(stock_env);
	v->freethis = 1;
}

static int		ft_tablen(char **t)
{
	int i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

static void		dispatch_set(char **nline, char *res, t_env *v, int mod)
{
	char *l;

	if (mod == 0)
	{
		free(res);
		change_env(nline[1], nline[0], v);
		free(nline[1]);
		free(nline[0]);
	}
	else
	{
		free(res);
		l = ft_strjoin_free(nline[0], "=", 0);
		if (nline[1])
			l = ft_strjoin_free(l, nline[1], 2);
		else
		{
			free(l);
			l = NULL;
		}
		new_env(l, v);
		free(l);
	}
}

int				ft_setenv(char **line, t_env *v)
{
	int		i;
	char	**nline;
	char	*res;

	i = 0;
	if (ft_tablen(line) != 2)
		return (ft_printf("wrong number of arguments\n"));
	while (line[++i])
	{
		nline = ft_split(line[i], '=');
		if (ft_tablen(nline) > 2)
		{
			free_tab(nline);
			return (ft_printf("wrong number of arguments\n"));
		}
		res = get_env(nline[0]);
		if (res != NULL && nline[1])
			dispatch_set(nline, res, v, 0);
		else
			dispatch_set(nline, res, v, 1);
	}
	free(nline);
	return (1);
}
