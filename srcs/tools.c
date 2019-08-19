/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:44:48 by ezonda            #+#    #+#             */
/*   Updated: 2019/08/19 13:58:23 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

void	init_shell(t_var *data)
{
	data->pos = 0;
}

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**dest;

	i = 0;
	while (tab[i])
		i++;
	if (!(dest = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		dest[i] = ft_strdup(tab[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
