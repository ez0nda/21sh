/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:25:49 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 16:03:01 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int				ft_nbrsize(long nb)
{
	int		size;

	size = 0;
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	if (nb == 0)
		size++;
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

void			ft_print_hexa2(t_struct *stru, t_stock *stock)
{
	while (stru->stock_pre-- > pf_strlen(stock->stock_s))
		pf_putchar('0', stru);
	if (stru->indic == 'p')
		pf_putstr("0x", stru);
	if (stru->indic == 's' || stru->indic == 'p')
	{
		if ((stru->flag[10] == 1 && (stru->prec != 0
			|| pf_strcmp(stock->stock_s, "0") != 0)) || (stru->flag[10] == 0))
			ft_putstr_free(stock->stock_s, stru);
		else if (stru->flag[10] == 1 && (stru->prec != 0
			|| pf_strcmp(stock->stock_s, "0") == 0) && stru->stock_pad > 0)
			pf_putchar(' ', stru);
	}
	if (stru->prec != 0)
		while (stru->stock_pad-- > stru->prec)
			pf_putchar(' ', stru);
	else
		while (stru->stock_pad-- > pf_strlen(stock->stock_s))
			pf_putchar(' ', stru);
}

void			ft_print_hs(t_struct *stru, t_stock *stock)
{
	if (stru->flag[2] == 0 && ((stru->flag[10] == 1 && (stru->prec != 0
			|| pf_strcmp(stock->stock_s, "0") != 0)) || (stru->flag[10] == 0))
			&& stru->indic == 's')
		ft_prec_p(stru, stock);
	else if (stru->flag[2] == 0 && ((stru->flag[10] == 1 && (stru->prec != 0
			|| pf_strcmp(stock->stock_s, "0") != 0)) || (stru->flag[10] == 0)))
		ft_putstr_free(stock->stock_s, stru);
	else if (stru->flag[10] == 1 && (stru->prec != 0
				|| pf_strcmp(stock->stock_s, "0") == 0)
			&& stru->min_field > 0 && (stru->indic == 'x'
				|| stru->indic == 'X'))
		pf_putchar(' ', stru);
}

void			ft_indic_p(t_struct *stru, t_stock *stock)
{
	stru->flag[8] = 1;
	ft_indic_x(stru, stock);
}

void			ft_print_hexa(t_struct *stru, t_stock *stock)
{
	stru->stock_pre = stru->prec;
	stru->stock_pad = stru->min_field;
	if (stru->flag[2] == 0)
	{
		while (stru->stock_pad > pf_strlen(stock->stock_s)
				&& stru->stock_pad > stru->prec && stru->indic == 'x')
		{
			pf_putchar(' ', stru);
			stru->stock_pad--;
		}
		while (stru->stock_pad > 14
				&& stru->stock_pad > stru->prec && stru->indic == 'p')
		{
			pf_putchar(' ', stru);
			stru->stock_pad--;
		}
		while (stru->stock_pre-- > pf_strlen(stock->stock_s))
			pf_putchar('0', stru);
	}
	else
		ft_print_hexa2(stru, stock);
}
