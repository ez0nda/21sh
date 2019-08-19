/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:20:02 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:45:48 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		ft_number_of_words(const char *str, char c)
{
	int i;
	int j;
	int counter;

	i = 0;
	j = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			j = 0;
		}
		else
		{
			if (j == 0)
				counter++;
			j = 1;
			i++;
		}
	}
	return (counter);
}

static char		**ft_fill_tab(const char *str, int i, char c, char **tab)
{
	int l;
	int j;

	l = 0;
	j = 0;
	while (str[l] == c)
		l++;
	while (str[l])
	{
		j = 0;
		while (str[l] != c && str[l])
		{
			tab[i][j] = str[l];
			j++;
			l++;
		}
		while (str[l] == c)
		{
			l++;
			tab[i][j] = '\0';
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		words;
	char	**tab;

	i = 0;
	if (!(s))
		return (NULL);
	words = ft_number_of_words(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	while (i < words)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		i++;
	}
	i = 0;
	ft_fill_tab(s, i, c, tab);
	return (tab);
}
