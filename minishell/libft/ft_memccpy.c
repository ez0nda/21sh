/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:06:54 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/10 18:20:54 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char*)src;
	ptr2 = (unsigned char*)dest;
	i = 0;
	if (ptr1 == ptr2)
		return (dest);
	while (i < n)
	{
		ptr2[i] = ptr1[i];
		if (ptr1[i] == (unsigned char)c)
			return ((void*)ptr2 + i + 1);
		i++;
	}
	return (NULL);
}
