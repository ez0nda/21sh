/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:10:23 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:39:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *s1;
	char *s2;

	s1 = (char*)src;
	s2 = (char*)dst;
	if (s1 < s2)
	{
		s1 = s1 + len - 1;
		s2 = s2 + len - 1;
		while (len > 0)
		{
			*s2-- = *s1--;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*s2++ = *s1++;
			len--;
		}
	}
	return (dst);
}
