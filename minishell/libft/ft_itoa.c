/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:07:43 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 13:23:09 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_rev(char *s)
{
	char	*s_rev;
	int		i;
	int		j;

	j = ft_strlen(s) - 1;
	if (!(s_rev = (char*)malloc(sizeof(char) * j)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_rev[i] = s[j];
		i++;
		j--;
	}
	return (s_rev);
}

static int		ft_convert(char *dest, int n)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		dest[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	if (i == 0)
		return (1);
	return (i);
}

static char		*ft_malloc_n(int n)
{
	char	*dest;
	int		i;
	int		j;

	j = n;
	i = 0;
	while (j > 0)
	{
		j = j / 10;
		i++;
	}
	if (n <= 0)
		if (!(dest = (char*)malloc(sizeof(char) * (i + 2))))
			return (NULL);
	if (n > 0)
		if (!(dest = (char*)malloc(sizeof(char) * (i + 1))))
			return (NULL);
	return (dest);
}

static char		*ft_int_min(char *dest)
{
	dest[0] = '-';
	dest[1] = '2';
	dest[2] = '1';
	dest[3] = '4';
	dest[4] = '7';
	dest[5] = '4';
	dest[6] = '8';
	dest[7] = '3';
	dest[8] = '6';
	dest[9] = '4';
	dest[10] = '8';
	dest[11] = '\0';
	return (dest);
}

char			*ft_itoa(int n)
{
	int		j;
	int		i;
	char	*dest;

	j = 1;
	if ((dest = ft_malloc_n(n)) == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		dest = ft_int_min(dest);
		return (dest);
	}
	if (n < 0)
	{
		j = -1;
		n = -n;
	}
	if (n == 0 || n == -0)
		dest[0] = '0';
	i = ft_convert(dest, n);
	if (j == -1)
		dest[i++] = '-';
	dest[i] = '\0';
	dest = ft_rev(dest);
	return (dest);
}
