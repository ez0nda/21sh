/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:57:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:57:42 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_spaces(char *buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((buf[i] == ' ' || buf[i] == '\t') && buf[i])
		i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}

char	*rm_whitespace(char *buf, t_env *v)
{
	rm_spaces(buf);
	if (ft_strlen(buf) > 1)
		buf = expansions(buf, v);
	else
		buf = ft_strdup("\n");
	rm_spaces(buf);
	return (buf);
}

char	*first_whitespace(char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n') && buf[i])
		i++;
	while (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' && buf[i])
		i++;
	if (!(tmp = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		tmp[j] = buf[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	parse_arg(char *str, char c, t_env *v)
{
	int j;
	int i;

	i = -1;
	j = 0;
	if (!str)
		return ;
	while (str[++i])
	{
		if ((str[i] == c && str[i + 1] != c) || str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = 0;
	if (str[j - 1] == '-' && ft_strlen(str) == 1)
		v->istir = 1;
}

char	*parse_error(char *s, t_env *v)
{
	char	*save;
	char	**arg;
	int		i;

	i = -1;
	arg = ft_split(s, '/');
	if (s[0] == '/')
		save = ft_strdup("/");
	else
		save = get_env_val(v->pwd);
	while (arg[++i])
	{
		if (strcmp(arg[i], "..") == 0)
			rm_error(save);
		else if (s[i])
			save = add_error(save, arg[i]);
		free(arg[i]);
	}
	parse_arg(save, '/', v);
	free(arg);
	return (save);
}
