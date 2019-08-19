/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:43:51 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:32:46 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int n;
	int neg;

	i = 0;
	n = 0;
	neg = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\r') ||
		(str[i] == '\n') || (str[i] == '\f') || (str[i] == '\v'))
		i++;
	if (str[i] == '-')
		neg = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	if (str[i] < '0' || str[i] == 92)
		return (0);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		n = n * 10;
		n = n + str[i] - '0';
		i++;
	}
	if (neg == 1)
		n = -n;
	return (n);
}
