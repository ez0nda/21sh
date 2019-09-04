/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:22:25 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 13:23:37 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
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
