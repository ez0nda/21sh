/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 10:16:49 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:35:35 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_checkerror(int fd, char **line, char **str)
{
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || fd >= OPEN_MAX)
		return (-1);
	if (!str[fd])
		if (!(str[fd] = ft_strnew(0)))
			return (-1);
	return (0);
}

static int	ft_readline(const int fd, char **str)
{
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	if ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (!(tmp = ft_strdup(*str)))
			return (-1);
		ft_strdel(str);
		if (!(*str = ft_strjoin(tmp, buffer)))
			return (-1);
		ft_strdel(&tmp);
	}
	return (ret);
}

static int	ft_nextline(char **str, char *line_feed)
{
	char	*tmp;

	if (!(tmp = ft_strdup(line_feed + 1)))
		return (-1);
	ft_strdel(str);
	if (!(*str = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str[OPEN_MAX];
	char		*line_feed;
	int			ret;

	if (ft_checkerror(fd, line, str) == -1)
		return (-1);
	while (!(line_feed = ft_strchr(str[fd], '\n')))
	{
		if ((ret = ft_readline(fd, &str[fd])) < 0)
			return (-1);
		if (ret == 0 && !line_feed)
		{
			if (str[fd][0] == '\0')
				return (0);
			if (!(*line = ft_strdup(str[fd])))
				return (-1);
			str[fd][0] = '\0';
			return (1);
		}
	}
	if (!(*line = ft_strsub(str[fd], 0, line_feed - str[fd])))
		return (-1);
	if (ft_nextline(&str[fd], line_feed) == -1)
		return (-1);
	return (1);
}
