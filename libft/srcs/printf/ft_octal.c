/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:33:05 by jebrocho          #+#    #+#             */
/*   Updated: 2019/01/29 15:59:17 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char		*ft_convert_o(uintmax_t octal_int)
{
	int			i;
	char		*str;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * 23)))
		return (NULL);
	if (octal_int == 0)
		return (pf_strdup("0"));
	while (octal_int != 0)
	{
		str[i] = octal_int % 8 + 48;
		octal_int /= 8;
		i++;
	}
	str[i] = '\0';
	str = pf_strrev(str);
	return (str);
}

void		ft_minus_flag(t_struct *stru, int i)
{
	if (stru->flag[0] == 0)
		while (stru->min_field-- > i)
			pf_putchar(' ', stru);
	else
		while (stru->min_field-- > i)
			pf_putchar('0', stru);
}

void		ft_hash_flag2(t_struct *stru, t_stock *stock, int i)
{
	ft_minus_flag(stru, i);
	while (stru->prec-- > i)
		pf_putchar('0', stru);
	pf_putchar('0', stru);
	if (stock->stock_il != 0)
	{
		if (stru->flag[7] == 0 && stru->flag[8] == 0)
			pf_putnbr(stock->stock_il, stru);
		else
			pf_putstr(stock->stock_s, stru);
	}
}

void		ft_hash_flag(t_struct *stru, t_stock *stock)
{
	int i;

	if (stock->stock_il != 0)
		i = ft_nbrsize(stock->stock_il) + 1;
	else
		i = ft_nbrsize(stock->stock_il);
	if (stru->flag[2] == 1)
	{
		pf_putchar('0', stru);
		if (stock->stock_il != 0)
		{
			if (stru->flag[7] == 0 && stru->flag[8] == 0)
				pf_putnbr(stock->stock_il, stru);
			else
				pf_putstr(stock->stock_s, stru);
		}
		ft_minus_flag(stru, i);
		return ;
	}
	ft_hash_flag2(stru, stock, i);
}

void		ft_indic_o(t_struct *stru, t_stock *stock)
{
	stru->flag[4] = 0;
	stru->flag[3] = 0;
	if (stru->flag[5] == 1)
		stock->stock_h = 256;
	else if (stru->flag[6] == 1)
		stock->stock_h = 65536;
	else
		stock->stock_h = 4294967296;
	if (stock->stock_il >= stock->stock_h && stru->flag[7] == 0
			&& stru->flag[8] == 0)
		stock->stock_il = stock->stock_il % stock->stock_h;
	if ((stock->stock_s = ft_convert_o(stock->stock_il)) == NULL)
		return ;
	if (stru->flag[7] == 0 && stru->flag[8] == 0)
		stock->stock_il = pf_atoi(stock->stock_s);
	if (stru->flag[1] == 0)
		ft_indic_di(stru, stock);
	else
		ft_hash_flag(stru, stock);
	free(stock->stock_s);
}
