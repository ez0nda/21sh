/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:11:56 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/14 18:56:12 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && i < n)
	{
		while (s1[i + j] == s2[j] && s2[j] && (i + j) < n)
			j++;
		if (s2[j] == '\0')
			return ((char*)&s1[i]);
		else
			j = 0;
		i++;
	}
	return (NULL);
}
