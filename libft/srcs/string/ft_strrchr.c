/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 00:50:36 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:45:11 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;

	t = NULL;
	while (*s)
	{
		if (*s == (char)c)
			t = (char*)s;
		s++;
	}
	if (*s == (char)c)
		return ((char*)s);
	else
		return (t);
}
