/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:11:55 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:10:41 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int		strings_scan_whitespaces(
	char **p_input, char *end, char *search)
{
	char *tmp;

	tmp = *p_input;
	while (tmp < end && ft_strchr(" \t\r\n\v", *tmp))
		tmp++;
	*p_input = tmp;
	return (*tmp && ft_strchr(search, *tmp));
}

int		strings_scan_pipes(char **p_input, char *end,
	char **new_cmd, char **new_cmd_end)
{
	char *tmp;

	tmp = *p_input;
	while (tmp < end && ft_strchr(" \t\r\n\v", *tmp))
		tmp++;
	*new_cmd = tmp;
	while (tmp < end && !ft_strchr("|", *tmp))
		tmp++;
	*new_cmd_end = tmp;
	*p_input = tmp;
	return (tmp != end);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!(s2 = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
