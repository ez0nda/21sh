/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 13:55:40 by jebrocho          #+#    #+#             */
/*   Updated: 2019/01/29 16:03:32 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

intmax_t	ft_find_u(t_stock *stock, int i)
{
	if (i == 0)
	{
		if (stock->stock_il < 0 && stock->stock_il % stock->stock_h != 0)
			return (stock->stock_h + stock->stock_il % stock->stock_h);
		else if (stock->stock_il % stock->stock_h == 0)
			return (0);
		if (stock->stock_il > stock->stock_h)
			return (stock->stock_il % stock->stock_h);
		else
			return (stock->stock_il);
	}
	else
		return (stock->stock_il);
}

void		ft_indic_u(t_struct *stru, t_stock *stock)
{
	stru->flag[3] = 0;
	stru->flag[4] = 0;
	if (stru->flag[5] == 1)
		stock->stock_h = 256;
	else if (stru->flag[6] == 1)
		stock->stock_h = 65536;
	else
		stock->stock_h = 4294967296;
	if (stru->flag[7] == 0 && stru->flag[8] == 0)
		stock->stock_il = ft_find_u(stock, 0);
	else
		stock->stock_il = ft_find_u(stock, 1);
	ft_indic_di(stru, stock);
}
