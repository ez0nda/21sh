/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:41:02 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 16:03:29 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_toupper_mod(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 97 && s[i] <= 122)
			s[i] = s[i] - 32;
		i++;
	}
	return (s);
}

void	ft_apply_signe(t_struct *stru, t_stock *stock)
{
	if (stru->flag[3] == 1 && stock->stock_il >= 0)
		pf_putchar('+', stru);
	else if (stock->stock_il < 0 && stru->modl == 1)
	{
		stock->stock_il *= -1;
		pf_putchar('-', stru);
	}
}

void	ft_print_numbers(t_struct *stru, t_stock *stock, int i)
{
	while (stru->nb_carac-- > i - stru->stock_pre2)
		pf_putchar('0', stru);
	if (stock->stock_il == 0 && stru->flag[10] == 1 && stru->prec == 0)
		return ;
	if ((stru->flag[8] == 1 || stru->flag[7] == 1) && stru->indic == 'o')
		pf_putstr(stock->stock_s, stru);
	else if ((stru->flag[8] == 1 || stru->flag[7] == 1)
			&& stru->indic == 'u')
		pf_putnbr_l(stock->stock_il, stru);
	else
		pf_putnbr(stock->stock_il, stru);
}
