/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 17:56:09 by ezonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/28 20:51:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../../includes/ft_printf.h"

int		pf_strcmp(const char *s1, const char *s2)
{
	unsigned int i;

	i = 0;
	while ((s1[i]) && (s2[i]) && (s1[i] == s2[i]))
		i++;
	i = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (i);
}
