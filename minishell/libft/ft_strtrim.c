/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:44:05 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/12 16:32:53 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_print_carac(int *tab, char const *s, char *dest)
{
	while (tab[1] <= tab[2])
	{
		dest[tab[0]] = s[tab[1]];
		tab[0]++;
		tab[1]++;
	}
	dest[tab[0]] = '\0';
}

char			*ft_strtrim(char const *s)
{
	int		tab[3];
	char	*dest;

	if (!s)
		return (NULL);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = ft_strlen(s) - 1;
	while (s[tab[1]] == ' ' || s[tab[1]] == '\n' || s[tab[1]] == '\t')
		tab[1]++;
	while (s[tab[2]] == ' ' || s[tab[2]] == '\n' || s[tab[2]] == '\t')
		tab[2]--;
	if (tab[2] > tab[1])
	{
		if (!(dest = (char*)malloc(sizeof(char) * (tab[2] - tab[1]))))
			return (NULL);
	}
	else
	{
		if (!(dest = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
	}
	ft_print_carac(tab, s, dest);
	return (dest);
}
