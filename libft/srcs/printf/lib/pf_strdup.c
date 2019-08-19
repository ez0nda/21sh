/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:04:12 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 16:05:21 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*pf_strdup(const char *s)
{
	int		i;
	int		n;
	char	*dest;

	i = 0;
	n = 0;
	while (s[n])
		n++;
	if (!(dest = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
