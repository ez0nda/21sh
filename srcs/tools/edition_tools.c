/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:44:48 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/17 13:50:25 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		ft_putchar_v2(int c)
{
	write(1, &c, 1);
	return (c);
}

void	init_shell(t_var *data)
{
	int i;

	i = 0;
	data->pos = 0;
	data->char_count = 0;
	data->in_selection = 0;
	data->new_history = 0;
	data->left = 0;
	data->right = 0;
	data->quotes = 0;
	data->dquotes = 0;
	data->std_prompt = 1;
	if (!(data->lex_str = (char*)malloc(sizeof(char) * BUFF_SHELL)))
			return ;
	if (!(data->history = (char**)malloc(sizeof(char*) * BUFF_SHELL)))
		return ;
	if (!(data->selection = (char*)malloc(sizeof(char) * BUFF_SHELL)))
		return ;
	if (!(data->tab = malloc(sizeof(int) * BUFF_SHELL)))
		return ;
	if (!(data->stock = (char*)malloc(sizeof(char) * BUFF_SHELL)))
		return ;
	while (i < BUFF_SHELL)
	{
		data->tab[i] = 0;
		i++;
	}
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabdup(char **tab, int n)
{
	int		i;
	char	**dest;

	i = 0;
	while (tab[i])
		i++;
	i += n;
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
