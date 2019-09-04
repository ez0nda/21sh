/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:38:37 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 13:53:57 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int n, int power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	while (power > 1)
		return (n * ft_power(n, power - 1));
	return (0);
}
