/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 13:39:35 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 16:09:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_indic_di2(t_struct *stru, t_stock *stock)
{
	int i;

	if (stru->flag[5] == 1 && (stru->indic == 'i' || stru->indic == 'd'))
		stock->stock_il = (char)stock->stock_i;
	else if (stru->flag[6] == 1 && (stru->indic == 'i' || stru->indic == 'd'))
		stock->stock_il = (short int)stock->stock_i;
	else if (stru->flag[7] == 0 && stru->flag[8] == 0 && (stru->indic == 'i'
				|| stru->indic == 'd'))
		stock->stock_il = (int)stock->stock_i;
	if (stru->flag[3] == 1 || stock->stock_il < 0)
		stru->flag[4] = 0;
	if (stru->prec > ft_nbrsize(pf_abs(stock->stock_il)))
	{
		i = stru->prec;
		stru->stock_pre2 = i - ft_nbrsize(pf_abs(stock->stock_il));
	}
	else
		i = ft_nbrsize(stock->stock_il);
	return (i);
}

void	ft_indic_di(t_struct *stru, t_stock *stock)
{
	int i;

	i = ft_indic_di2(stru, stock);
	if ((stock->stock_il < 0 && stru->prec >
		ft_nbrsize(pf_abs(stock->stock_il))) || (stru->flag[3] == 1
		&& stock->stock_il >= 0))
		i++;
	if (i > stru->min_field)
		stru->nb_carac = i;
	else
		stru->nb_carac = stru->min_field;
	if (i == stru->nb_carac && stru->flag[4] == 1)
		pf_putchar(' ', stru);
	else if (stru->flag[0] == 1 && stru->flag[4] == 1)
	{
		stru->nb_carac--;
		pf_putchar(' ', stru);
	}
	if (stock->stock_il == 0 && stru->flag[10] == 1 && stru->prec == 0
			&& stru->min_field > 0)
		i--;
	if (stru->flag[2] == 0)
		ft_apply_flags(stru, stock, i);
	else
		ft_apply_flags2(stru, stock);
}

void	ft_apply_flags(t_struct *stru, t_stock *stock, int i)
{
	while (stru->nb_carac > i)
	{
		if (stru->flag[0] == 1 && stru->flag[10] == 0)
		{
			ft_apply_signe(stru, stock);
			stru->flag[3] = 0;
			stru->modl++;
			pf_putchar('0', stru);
		}
		else
			pf_putchar(' ', stru);
		stru->nb_carac--;
	}
	if (stru->flag[3] == 1 && stock->stock_il >= 0)
		pf_putchar('+', stru);
	else if (stock->stock_il < 0 && stru->modl == 1)
	{
		if (stru->flag[7] == 0 && stru->flag[8] == 0)
		{
			stock->stock_il *= -1;
			pf_putchar('-', stru);
		}
	}
	ft_print_numbers(stru, stock, i);
}

void	ft_print_numbers2(t_struct *stru, t_stock *stock)
{
	if (stock->stock_il != 0 || stru->flag[10] != 1 || stru->prec != 0)
	{
		if ((stru->flag[8] == 1 || stru->flag[7] == 1) && stru->indic == 'o')
			pf_putstr(stock->stock_s, stru);
		else if ((stru->flag[8] == 1 || stru->flag[7] == 1)
				&& stru->indic == 'u')
			pf_putnbr_l(stock->stock_il, stru);
		else
			pf_putnbr(stock->stock_il, stru);
		stru->nb_carac -= ft_nbrsize(stock->stock_il);
	}
	while (stru->nb_carac > 0)
	{
		pf_putchar(' ', stru);
		stru->nb_carac--;
	}
}

void	ft_apply_flags2(t_struct *stru, t_stock *stock)
{
	stru->stock_pre_f = stru->prec - ft_nbrsize(pf_abs(stock->stock_il));
	if (stru->flag[3] == 1 && stock->stock_il >= 0)
	{
		pf_putchar('+', stru);
		stru->nb_carac--;
	}
	else if (stock->stock_il < 0)
	{
		if (stru->flag[7] == 0 && stru->flag[8] == 0)
		{
			stru->nb_carac--;
			stock->stock_il *= -1;
			pf_putchar('-', stru);
		}
	}
	while (stru->stock_pre_f-- > 0)
	{
		pf_putchar('0', stru);
		stru->nb_carac--;
	}
	ft_print_numbers2(stru, stock);
}
