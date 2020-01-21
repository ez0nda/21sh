/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_putstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 10:05:10 by ezonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/28 20:51:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../../includes/ft_printf.h"

void	pf_putstr(const char *s, t_struct *stru)
{
	int i;

	i = 0;
	if (!(s))
		return ;
	while (s[i])
	{
		pf_putchar(s[i], stru);
		i++;
	}
}
