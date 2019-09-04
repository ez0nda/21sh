/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:24:49 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 11:00:33 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*sptr;

	sptr = (char*)s;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			if (sptr[i] == (char)c)
				return ((void*)&sptr[i]);
			i++;
		}
	}
	return (NULL);
}
