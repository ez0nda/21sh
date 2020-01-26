/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:36:36 by jebrocho          #+#    #+#             */
/*   Updated: 2020/02/05 14:33:12 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

char	*get_exp(char *str, int index)
{
	char	*selec;
	int		i;

	i = 0;
	selec = ft_strnew(BUFF_SHELL);
	while (str[index] > 64 && str[index] < 91)
	{
		selec[i] = str[index];
		i++;
		index++;
	}
	selec[i++] = '=';
	selec[i] = '\0';
	return (selec);
}

void	apply_exp(t_var *data, char *selec, int j, int i)
{
	int k;

	k = 0;
	ft_bzero(selec, ft_strlen(selec));
	while (data->qstr[j])
	{
		selec[k] = data->qstr[j];
		k++;
		j++;
	}
	selec[k] = '\0';
	data->qstr[i] = '\0';
}

void	join_exp(t_var *data, char *stock, char *selec)
{
	data->qstr = ft_strjoin_free(data->qstr, stock, 2);
	data->qstr = ft_strjoin_free(data->qstr, selec, 2);
}

void	algo_exp(t_var *data, int i)
{
	int		j;
	char	*selec;
	char	*stock;

	j = i + 1;
	while (data->qstr[j] > 64 && data->qstr[j] < 91)
		j++;
	if (j == ft_strlen(data->qstr) || data->qstr[j] == ' '
			|| data->qstr[j] == '\"'
			|| (data->qstr[j] == '\\' && data->qstr[j + 1] == '"'))
	{
		selec = get_exp(data->qstr, i + 1);
		stock = get_env(data->environ, selec);
		if (stock != NULL)
		{
			apply_exp(data, selec, j, i);
			join_exp(data, stock, selec);
		}
	}
}

void	add_exp(t_var *data)
{
	int		i;

	i = -1;
	while (data->qstr[++i])
		if (data->qstr[i] == '$')
			algo_exp(data, i);
}
