/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 11:16:06 by jebrocho          #+#    #+#             */
/*   Updated: 2019/01/31 20:01:08 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void		ft_flag_u(char *s, t_struct *stru)
{
	int i;

	i = pf_strlen(s);
	if (stru->flag[2] == 1 && stru->min_field > i)
	{
		ft_putstr_free(s, stru);
		while (stru->min_field-- > i)
			pf_putchar(' ', stru);
		return ;
	}
	if (stru->min_field > i)
	{
		if (stru->flag[0] == 1)
			while (stru->min_field-- > i)
				pf_putchar('0', stru);
		else
			while (stru->min_field-- > i)
				pf_putchar(' ', stru);
		ft_putstr_free(s, stru);
		return ;
	}
	ft_putstr_free(s, stru);
}

void		ft_add(t_struct *stru)
{
	if (stru->indic == 'x')
		pf_putstr("0x", stru);
	else
		pf_putstr("0X", stru);
}

void		ft_flag(t_struct *stru, t_stock *stock, int i)
{
	if (stru->flag[2] == 1)
	{
		ft_add(stru);
		ft_putstr_free(stock->stock_s, stru);
		while (stru->min_field-- > i)
			pf_putchar(' ', stru);
		return ;
	}
	if (stru->flag[0] == 1)
	{
		ft_add(stru);
		while (stru->min_field-- > i)
			pf_putchar('0', stru);
		ft_putstr_free(stock->stock_s, stru);
		return ;
	}
}

void		ft_print_has_hexa(t_struct *stru, t_stock *stock)
{
	int i;

	i = pf_strlen(stock->stock_s) + 2;
	if (stock->stock_il == 0 && stru->flag[10] == 0)
	{
		pf_putchar('0', stru);
		return ;
	}
	else if (stock->stock_il == 0 && stru->flag[10] == 1)
		return ;
	if (stru->flag[2] == 1 || stru->flag[0] == 1)
	{
		ft_flag(stru, stock, i);
		return ;
	}
	while (stru->min_field-- > i)
		pf_putchar(' ', stru);
	ft_add(stru);
	while (stru->prec-- > pf_strlen(stock->stock_s))
		pf_putchar('0', stru);
	ft_putstr_free(stock->stock_s, stru);
}
