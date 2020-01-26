/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:50:07 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/03 12:51:25 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	update_history(t_var *data)
{
	int		i;
	int		hist;
	int		back_fd;
	char	*str;

	i = 0;
	str = ft_strjoin(getenv("HOME"), "/.21sh_history");
	hist = open(str, O_WRONLY, O_APPEND);
	if (hist == -1)
	{
		free(str);
		return ;
	}
	back_fd = dup(1);
	dup2(hist, 1);
	while (data->history[i])
		ft_putendl(data->history[i++]);
	close(hist);
	dup2(back_fd, 1);
	free(str);
}

void	get_history(t_var *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (get_next_line(fd, &line) == 1 && i < BUFF_SHELL)
	{
		data->history[i] = ft_strdup(line);
		free(line);
		i++;
	}
}

void	manage_history(t_var *data)
{
	int		fd;
	char	*str;

	str = ft_strjoin(getenv("HOME"), "/.21sh_history");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		fd = open(str, O_CREAT, S_IRUSR | S_IWUSR);
	else
		get_history(data, fd);
	free(str);
}

int		is_empty(t_var *data)
{
	int i;

	i = 0;
	while (is_whitespaces(data->lex_str[i]))
		i++;
	if (i == ft_strlen(data->lex_str))
		return (1);
	return (0);
}
