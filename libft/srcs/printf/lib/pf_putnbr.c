/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 10:25:08 by ezonda       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 19:34:57 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../../../includes/ft_printf.h"

void	pf_putnbr_l(uintmax_t nb, t_struct *stru)
{
	if (nb > 9)
	{
		pf_putnbr_l(nb / 10, stru);
		pf_putnbr_l(nb % 10, stru);
	}
	else
	{
		nb = nb + '0';
		pf_putchar(nb, stru);
	}
}

void	pf_putnbr(long n, t_struct *stru)
{
	long nb;

	nb = n;
	if (stru->modl == 0)
	{
		pf_putstr("-9223372036854775808", stru);
		return ;
	}
	if (nb < 0)
	{
		pf_putchar('-', stru);
		nb = -nb;
	}
	if (nb > 9)
	{
		pf_putnbr(nb / 10, stru);
		pf_putnbr(nb % 10, stru);
	}
	else
	{
		nb = nb + '0';
		pf_putchar(nb, stru);
	}
}
