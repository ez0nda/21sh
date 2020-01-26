/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:48:59 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/03 11:44:12 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void		add_to_files(t_var *data, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->files[i])
		i++;
	while (str[j])
	{
		data->files[i] = str[j];
		i++;
		j++;
	}
	data->files[i++] = ' ';
	data->files[i] = '\0';
}

void		update_files(t_var *data)
{
	int		fd;
	int		back_fd;
	char	*line;
	char	**split;

	split = ft_strsplit(data->files, ' ');
	fd = open(split[0], O_RDONLY, O_APPEND);
	back_fd = dup(1);
	dup2(fd, 1);
}

char		*rm_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
			i = 0;
		}
		i++;
	}
	return (str);
}

void		add_to_here_stock(char c, t_var *data)
{
	int		i;
	char	tmp[BUFF_SHELL];

	i = 0;
	while (data->here_stock[i])
	{
		tmp[i] = data->here_stock[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = '\0';
	free(data->here_stock);
	data->here_stock = ft_strdup(tmp);
}

void		rm_herend(t_var *data)
{
	int i;

	i = ft_strlen(data->here_stock);
	while (data->here_stock[i] != '\n')
	{
		data->here_stock[i] = '\0';
		i--;
	}
	data->here_stock[i] = '\0';
}
