/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indic_csp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 13:39:35 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 15:57:46 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_indic_c(t_struct *stru, t_stock *stock)
{
	int i;

	i = 1;
	if (stru->flag[2] == 1)
		pf_putchar(stock->stock_c, stru);
	if (stru->flag[0] == 1 && stru->flag[2] == 0)
	{
		while (stru->min_field > i)
		{
			pf_putchar('0', stru);
			stru->min_field--;
		}
	}
	while (stru->min_field > i)
	{
		pf_putchar(' ', stru);
		i++;
	}
	if (stru->flag[2] == 0)
		pf_putchar(stock->stock_c, stru);
}

void	ft_indic_s(t_struct *stru, t_stock *stock)
{
	if (!stock->stock_s)
		stock->stock_s = "(null)";
	if (stru->indic == 's' && stru->prec < pf_strlen(stock->stock_s)
			&& stru->prec != 0)
		stock->stock_s = pf_strsub(stock->stock_s, 0, stru->prec);
	if (stru->flag[2] == 1 && stru->indic == 'p')
		pf_putstr("0x", stru);
	if (stru->flag[2] == 1 && (stru->indic == 's' || stru->indic == 'x')
			&& stru->flag[1] == 0)
		pf_putstr(stock->stock_s, stru);
	if (stru->flag[2] == 1 && stru->indic == 'p' && stock->stock_il != 0)
		pf_putstr(stock->stock_s, stru);
	else if (stru->flag[2] == 1 && stock->stock_il == 0 && stru->indic == 'p')
		pf_putchar('0', stru);
	if (stru->flag[0] == 1 && stru->flag[1] == 0 && stru->flag[2] == 0)
	{
		while ((stru->min_field > pf_strlen(stock->stock_s))
				&& (stru->indic == 's' || stru->prec == 0))
		{
			pf_putchar('0', stru);
			stru->min_field--;
		}
	}
	ft_print_str(stru, stock);
}

void	ft_print_str(t_struct *stru, t_stock *stock)
{
	stru->stock_pad = stru->min_field;
	while (stru->min_field > pf_strlen(stock->stock_s) && stru->indic == 's')
	{
		pf_putchar(' ', stru);
		stru->min_field--;
	}
	if (stru->indic == 'p')
	{
		while (stock->stock_il != 0
				&& stru->stock_pad > pf_strlen(stock->stock_s) + 2)
		{
			pf_putchar(' ', stru);
			stru->stock_pad--;
		}
		while (stock->stock_il == 0 && stru->stock_pad > stru->prec + 2)
		{
			pf_putchar(' ', stru);
			stru->stock_pad--;
		}
	}
	ft_print_str2(stru, stock);
}

void	ft_prec_p(t_struct *stru, t_stock *stock)
{
	int i;

	i = 0;
	if (stru->flag[10] == 1 && stru->prec == 0)
	{
		while (i++ < pf_strlen(stock->stock_s))
		{
			if (stru->flag[0] == 0)
				pf_putchar(' ', stru);
			else
			{
				pf_putstr("00000", stru);
				break ;
			}
		}
	}
	else
		pf_putstr(stock->stock_s, stru);
}

void	ft_print_str2(t_struct *stru, t_stock *stock)
{
	if ((stru->indic == 'x' || stru->indic == 'X') && stru->flag[1] == 0)
		ft_print_hexa(stru, stock);
	else if ((stru->indic == 'x' || stru->indic == 'X') && stru->flag[1] == 1)
	{
		ft_print_has_hexa(stru, stock);
		return ;
	}
	if (stru->indic == 'p' && stru->flag[2] == 0
			&& stock->stock_il != 0 && stru->flag[10] == 0)
		pf_putstr("0x", stru);
	else if (stru->indic == 'p' && stru->flag[2] == 0 && stock->stock_il == 0
			&& stru->flag[10] == 1 && stru->stock_pre == 0)
		pf_putstr("0x", stru);
	else if (stru->indic == 'p' && stru->flag[2] == 0
			&& stru->flag[10] == 1 && stru->stock_pre != 0)
	{
		pf_putstr("0x", stru);
		while (stru->prec-- > pf_strlen(stock->stock_s))
			pf_putchar('0', stru);
	}
	else if (stru->indic == 'p' && stru->flag[2] == 0 && stock->stock_il == 0
			&& stru->flag[10] == 0)
		pf_putstr("0x0", stru);
	ft_print_hs(stru, stock);
}
