/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:09:30 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 16:04:16 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_strsize(long nb)
{
	int			size;

	size = 0;
	if (nb == 0)
		size++;
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb > 0)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char			*pf_itoa(long nb)
{
	int			i;
	long		n;
	char		*str;

	i = 0;
	n = nb;
	if (n / 10 == -922337203685477580)
		return (pf_strdup("-9223372036854775808"));
	if (!(str = pf_strnew(ft_strsize(n))))
		return (NULL);
	if (nb < 0)
		nb = -nb;
	if (nb == 0)
		str[i++] = '0';
	while (nb > 0)
	{
		str[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	pf_strrev(str);
	return (str);
}
