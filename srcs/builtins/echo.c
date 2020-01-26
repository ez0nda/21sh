/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:32:18 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/03 12:02:07 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int		check_flag_n(char *cmd)
{
	int		count;
	char	**split;

	count = 0;
	split = NULL;
	if (!ft_strcmp(cmd, "-n"))
		return (1);
	split = ft_split(cmd, '"');
	if (!split[0])
	{
		free_tab(split);
		return (1);
	}
	if (!ft_strcmp(split[0], "-n"))
	{
		free_tab(split);
		return (1);
	}
	free_tab(split);
	return (0);
}

char	*rm_quotes(char *cmd, int count)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(cmd) - count;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (cmd[i])
	{
		while (cmd[i] == '"')
			i++;
		new[j] = cmd[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

void	print_echo(t_var *data, char **cmd, int i)
{
	int k;

	k = 0;
	while (cmd[i][k] && cmd[i][k] != '\\')
	{
		ft_putchar(cmd[i][k]);
		k++;
	}
	if (cmd[i][k] == '\\')
		k++;
	if (cmd[i][k] == 'n' && data->mod_quotes)
	{
		ft_putchar('\n');
		k++;
	}
	ft_putstr(&cmd[i][k]);
	if (cmd[i + 1])
		ft_putchar(' ');
}

void	parse_echo(t_var *data, char **cmd, int i)
{
	int j;
	int k;
	int count;

	k = 0;
	while (cmd[i])
	{
		j = 0;
		count = 0;
		while (cmd[i][j])
			if (cmd[i][j++] == '"')
				count++;
		if (ft_strchr(cmd[i], '"'))
			cmd[i] = rm_quotes(cmd[i], count);
		print_echo(data, cmd, i);
		i++;
	}
}

int		echo_builtin(t_var *data, char **cmd)
{
	int i;
	int flag_n;

	i = 1;
	flag_n = 0;
	if (!cmd[1])
	{
		free_tab(cmd);
		ft_putchar('\n');
		return (1);
	}
	while (check_flag_n(cmd[i]))
	{
		i++;
		flag_n = 1;
		if (!cmd[i])
		{
			free_tab(cmd);
			return (1);
		}
	}
	parse_echo(data, cmd, i);
	ft_putstr(flag_n ? "" : "\n");
	free_tab(cmd);
	return (1);
}
