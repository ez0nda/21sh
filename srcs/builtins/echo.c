/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:28:56 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/06 15:41:14 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	rm_echo(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

int		detect_echo(char **line)
{
	int i;

	i = -1;
	if (ft_strcmp(line[0], "echo") == 0)
	{
		while (line[++i])
			free(line[i]);
		free(line);
		return (0);
	}
	return (1);
}

void	rm_cote(char *line)
{
	int i;
	int j;
	int k;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			k = i;
			j = i + 1;
			while (line[j])
			{
				line[k] = line[j];
				k++;
				j++;
			}
			line[k] = '\0';
		}
	}
}

int		algo_cote(char *line, int i)
{
	int index;
	int new_id;

	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	index = i + 1;
	new_id = index;
	while (line[i] && (line[new_id] == ' ' || line[new_id] == '\t'))
		new_id++;
	while (line[new_id])
	{
		line[index] = line[new_id];
		index++;
		new_id++;
	}
	line[index] = '\0';
	return (i);
}

int 	echo_builtin(char **cmd)
{
	int i;
//	int id_cote;

	i = -1;
	while (cmd[++i])
		ft_printf("%s\n", cmd[i]);
/*	rm_echo(str);
	id_cote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			id_cote++;
		if (id_cote % 2 == 0)
			i = algo_cote(str, i);
	}
	rm_cote(str);
	ft_printf("%s", str);
	free(str);*/
	return (1);
}
