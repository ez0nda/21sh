/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:21:14 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/01 11:21:12 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

static int		ft_number_of_words(const char *str)
{
	int i;
	int j;
	int counter;

	i = 0;
	j = 0;
	counter = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]) == 1)
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

static char		**ft_fill_tab(const char *str, int i, char **tab)
{
	int l;
	int j;

	l = 0;
	j = 0;
	while (ft_is_whitespace(str[l]) == 1)
		l++;
	while (str[l])
	{
		j = 0;
		while (ft_is_whitespace(str[l]) != 1 && str[l])
		{
			tab[i][j] = str[l];
			j++;
			l++;
		}
		while (ft_is_whitespace(str[l]) == 1)
		{
			l++;
			tab[i][j] = '\0';
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char			**ft_strsplit_ws(char const *s)
{
	int		i;
	int		words;
	char	**tab;

	i = 0;
	if (!(s))
		return (NULL);
	words = ft_number_of_words(s);
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	while (i < words)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		i++;
	}
	i = 0;
	ft_fill_tab(s, i, tab);
	return (tab);
}
