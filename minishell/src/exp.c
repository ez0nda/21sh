/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 11:20:02 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:30:53 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exp(char *stock, int index)
{
	int		i;
	char	*exp;
	char	*s;

	i = 0;
	while (stock[index + i])
		i++;
	if (i == index + 1)
	{
		free(stock);
		return (ft_strdup("$"));
	}
	if (!(exp = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	index++;
	while (stock[index])
		exp[i++] = stock[index++];
	exp[i] = '\0';
	s = get_env(exp);
	if (s != NULL)
		free(stock);
	free(exp);
	return (s);
}

char	*parse_exp(char *stock, char *exp)
{
	int i;

	i = 0;
	while (stock[i] != '$' && stock[i])
		i++;
	stock[i] = '\0';
	return (ft_strjoin(stock, exp));
}

int		save_exp(char **stock, int i, int j, t_env *v)
{
	char	save[255];
	int		k;

	k = 0;
	if (stock[i][j] == '~' && (stock[i][j + 1] == '/' || j == 0))
	{
		while (stock[i][++j])
			save[k++] = stock[i][j];
		save[k] = 0;
		free(stock[i]);
		stock[i] = get_env_val(v->home);
		stock[i] = ft_strjoin_free(stock[i], save, 0);
	}
	return (j);
}

void	disp_dol(char **stock, int i, int j)
{
	char		*exp;

	if (stock[i][j] == '$')
	{
		exp = get_exp(stock[i], j);
		if (exp != NULL)
			stock[i] = parse_exp(stock[i], exp);
		else
			stock[i][j] = '\0';
		free(exp);
	}
}

char	*expansions(char *buf, t_env *v)
{
	char	**stock;
	int		i;
	int		j;

	i = -1;
	stock = ft_split_whitespace_exp(buf);
	while (stock[++i])
	{
		j = -1;
		while (stock[i][++j])
		{
			disp_dol(stock, i, j);
			j = save_exp(stock, i, j, v);
		}
	}
	i = 0;
	buf = stock[0];
	while (stock[++i])
	{
		buf = ft_strjoin_free(buf, " ", 0);
		buf = ft_strjoin_free(buf, stock[i], 2);
	}
	free(stock);
	buf = ft_strjoin_free(buf, "\n", 0);
	return (buf);
}
