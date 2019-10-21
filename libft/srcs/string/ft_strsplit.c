/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:48:18 by jebrocho          #+#    #+#             */
/*   Updated: 2019/10/21 08:54:22 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		ft_count_word(char const *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			j++;
		while (str[i] != c && str[i])
			i++;
	}
	return (j);
}

static char		*ft_print_word(char const *str, char c, int *i)
{
	char	*str_p;
	int		k;
	int		j;

	k = 0;
	j = 0;
	while (str[*i] == c && str[*i])
		*i = *i + 1;
	k = *i;
	while (str[k] != c && str[k])
		k++;
	if (!(str_p = (char*)malloc(sizeof(char) * (k - *i))))
		return (NULL);
	while (str[*i] != c && str[*i])
	{
		str_p[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	str_p[j] = '\0';
	return (str_p);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!str)
		return (NULL);
	if (!(split = (char**)malloc(sizeof(char*) * ft_count_word(str, c) + 1)))
		return (NULL);
	while (++j < ft_count_word(str, c))
		split[j] = ft_print_word(str, c, &i);
	split[j] = 0;
	return (split);
}
