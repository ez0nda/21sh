/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:04:27 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/06 15:46:27 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		count_word(char *str, char c)
{
	int	nb_word;
	int i;

	i = 0;
	nb_word = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		while (str[i] != c && str[i])
			i++;
		nb_word += 1;
		while (str[i] == c && str[i])
			i++;
	}
	return (nb_word);
}

static char		*split_word(char *str, char c)
{
	int			save;
	int			size;
	char		*word;
	static int	i;

	size = 0;
	while ((str[i] == c) && str[i])
		i++;
	save = i;
	while (str[i] != c && str[i])
		i++;
	if (!(word = (char*)malloc(sizeof(char) * (i - save + 1))))
		return (NULL);
	while (save < i)
	{
		word[size] = str[save];
		size++;
		save++;
	}
	word[size] = '\0';
	if (str[i] == '\0')
		i = 0;
	return (word);
}

char			**ft_split(char *str, char c)
{
	char	**split;
	int		nb_word;
	int		i;

	i = 0;
	nb_word = count_word(str, c);
	if (!(split = (char**)malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	while (i < nb_word)
	{
		split[i] = split_word(str, c);
		i++;
	}
	split[i] = NULL;
	return (split);
}
