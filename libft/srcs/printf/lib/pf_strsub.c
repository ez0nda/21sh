/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:37:57 by ezonda       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 19:34:57 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../../../includes/ft_printf.h"

char	*pf_strsub(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	sub = NULL;
	i = 0;
	if (!(s))
		return (NULL);
	if (!(sub = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
