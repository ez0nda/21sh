/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:06:41 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/23 13:58:33 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_cpy_end(char **buff, char **line)
{
	if (*buff != NULL)
	{
		if (!(*line = ft_strdup(*buff)))
			return (-1);
		ft_bzero(*buff, ft_strlen(*buff));
		return (1);
	}
	*line = NULL;
	return (0);
}

char		*ft_reader(char *buff, int *ret, int fd)
{
	char	tempo[BUFF_SIZE + 1];
	char	*tmpdel;

	*ret = read(fd, tempo, BUFF_SIZE);
	tempo[*ret] = '\0';
	tmpdel = buff;
	if (!(buff = ft_strjoin(buff, tempo)))
		return (NULL);
	ft_strdel(&tmpdel);
	return (buff);
}

int			ft_ecriture(char *str, char **buff, char **line, int fd)
{
	*str = '\0';
	if ((*line = ft_strdup(buff[fd])) == NULL)
		return (-1);
	buff[fd] = ft_memmove(buff[fd], str + 1, ft_strlen(str + 1) + 1);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char			*str;
	static char		*buff[OPEN_MAX];
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (!(buff[fd]) && (!(buff[fd] = ft_strnew(0))))
		return (-1);
	ret = 1;
	while (ret > 0)
	{
		if ((str = ft_strchr(buff[fd], '\n')))
			return (ft_ecriture(str, buff, line, fd));
		if ((buff[fd] = ft_reader(buff[fd], &ret, fd)) == NULL)
			return (-1);
	}
	ft_strdel(&str);
	if (ret == 0 && ft_strlen(buff[fd]))
		ret = ft_cpy_end(&buff[fd], &*line);
	else
		*line = NULL;
	return (ret);
}
