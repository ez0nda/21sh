/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indic_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 14:12:44 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/29 16:07:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_putstr_free(char *s, t_struct *stru)
{
	long i;

	i = 0;
	while (s[i])
	{
		pf_putchar(s[i], stru);
		i++;
	}
	free(s);
}

long	pf_abs(long nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

void	ft_indic_mod(t_struct *stru)
{
	int i;

	i = 1;
	if (stru->flag[2] == 1)
		pf_putchar('%', stru);
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
		pf_putchar('%', stru);
}
