/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 04:51:13 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:42:46 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s1[i] && i < size)
		i++;
	while (s2[n] && (i + n + 1) < size)
	{
		s1[i + n] = s2[n];
		n++;
	}
	if (i < size)
		s1[i + n] = '\0';
	return (i + ft_strlen(s2));
}
