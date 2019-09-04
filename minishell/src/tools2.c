/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:13:14 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:36:53 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_line(char *buf)
{
	int		i;
	char	**line;

	i = -1;
	if (buf[0] == '"')
		line = parse_command(buf);
	else
		line = ft_split_whitespace(buf);
	i = detect_echo(line);
	if (i == 0)
		return (ft_echo(buf));
	return (line);
}

void	rm_one(char *buf, int k)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	if (k == 1)
		j--;
	buf[j--] = '\0';
	if (k == 1)
		buf[j] = '\n';
}

char	**parse_command(char *buf)
{
	char	**line;
	char	*tmp;

	rm_one(buf, 1);
	tmp = first_whitespace(buf);
	line = ft_split_whitespace(buf);
	free(line[0]);
	line[0] = ft_strdup(tmp);
	free(tmp);
	return (line);
}
