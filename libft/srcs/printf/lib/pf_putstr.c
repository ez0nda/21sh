/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_putstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 10:05:10 by ezonda       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 19:34:57 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../../../includes/ft_printf.h"

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
