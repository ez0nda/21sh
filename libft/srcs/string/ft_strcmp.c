/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:56:09 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/23 16:32:02 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i]) && (s2[i]) && (s1[i] == s2[i]))
		i++;
	i = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (i);
}
