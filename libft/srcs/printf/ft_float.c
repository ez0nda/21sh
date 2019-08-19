/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:29:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/01/29 16:08:43 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_prec(t_struct *stru, long double f)
{
	int i;
	int nb;

	i = 0;
	while (i < stru->prec - 1)
	{
		f = f * 10;
		nb = f;
		pf_putnbr(nb, stru);
		f = f - nb;
		i++;
	}
	f = f * 100;
	nb = f;
	if (nb % 10 >= 5)
		nb = nb + 10;
	nb = nb / 10;
	pf_putnbr(nb, stru);
}

void	ft_print_dec(long double f, t_struct *stru)
{
	long	nb;
	int		i;

	i = 0;
	if (stru->prec > 0)
		ft_prec(stru, f);
	else
	{
		while (i < 6)
		{
			f *= 10;
			nb = (int)f;
			f = f - nb;
			i++;
			if (i != 6)
				pf_putnbr(nb, stru);
		}
		if (nb % 10 >= 5)
			nb = nb + 10;
		nb = nb / 10;
		pf_putnbr(nb, stru);
	}
}

size_t	ft_fnbrsize(double f, t_struct *stru)
{
	size_t		i;
	int			j;

	if (f >= 0.000000)
		i = 1;
	else
		i = 2;
	j = f;
	i += ft_nbrsize(j);
	if (stru->flag[10] == 1 && stru->prec != 0)
		i += stru->prec;
	else if (stru->flag[10] == 1 && stru->prec == 0)
	{
		i--;
		return (i);
	}
	else if (stru->flag[10] == 0)
		i += 6;
	return (i);
}

void	ft_print_float(long double f, t_struct *stru)
{
	long		nb_ent;
	size_t		pad2;

	pad2 = ft_fnbrsize(f, stru);
	if (f < 0)
		pf_putchar('-', stru);
	f = pf_abs(f);
	nb_ent = f;
	f = f - nb_ent;
	pf_putnbr(nb_ent, stru);
	pf_putchar('.', stru);
	ft_print_dec(f, stru);
}

void	ft_indic_f(t_struct *stru, t_stock *stock)
{
	ft_print_float(stock->stock_f, stru);
}
