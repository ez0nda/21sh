/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:14:15 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:46:00 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *)str);
	while (str[i])
	{
		while ((str[i + j] == to_find[j]) && (str[i]) && (to_find[j]))
		{
			j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
		}
		j = 0;
		i++;
	}
	return (0);
}
