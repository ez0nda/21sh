/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:37:51 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:52:12 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **t)
{
	char	**tab2;
	int		j;

	j = 0;
	while (t[j])
		j++;
	if (!(tab2 = (char**)malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	j = -1;
	while (t[++j])
		tab2[j] = ft_strdup(t[j]);
	tab2[j] = NULL;
	return (tab2);
}
