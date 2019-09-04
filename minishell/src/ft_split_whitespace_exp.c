/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace_exp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:37:30 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 08:39:56 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		count_word(char *str)
{
	int	nb_word;
	int i;

	i = 0;
	nb_word = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
		i++;
	while (str[i])
	{
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			i++;
		nb_word += 1;
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
			i++;
	}
	return (nb_word);
}

static char		*split_word(char *str, int *i)
{
	int			save;
	int			size;
	char		*word;

	size = 0;
	if ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n') && str[*i])
		(*i)++;
	save = *i;
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n') && str[*i])
		(*i)++;
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\n' && str[*i])
		(*i)++;
	if (!(word = (char*)malloc(sizeof(char) * (*i))))
		return (NULL);
	while (save < *i)
	{
		word[size] = str[save];
		size++;
		save++;
	}
	word[size] = '\0';
	return (word);
}

char			**ft_split_whitespace_exp(char *str)
{
	char	**split;
	int		nb_word;
	int		i;
	int		ptr;

	ptr = 0;
	i = 0;
	nb_word = count_word(str);
	if (!(split = (char**)malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	while (i < nb_word)
	{
		split[i] = split_word(str, &ptr);
		i++;
	}
	split[i] = NULL;
	return (split);
}
