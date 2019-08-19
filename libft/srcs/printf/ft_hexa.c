/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:58:50 by jebrocho          #+#    #+#             */
/*   Updated: 2019/01/29 15:54:58 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static char			*ft_convert_hexa2(t_stock *stock, char *str)
{
	int i;
	int rest;

	i = 0;
	stock->stock_il = stock->stock_il % stock->stock_h;
	while (stock->stock_il >= 0)
	{
		rest = stock->stock_il % 16;
		if (rest < 10)
			str[i] = rest + 48;
		else
			str[i] = rest + 87;
		stock->stock_il = stock->stock_il / 16;
		if (stock->stock_il == 0)
			stock->stock_il = -1;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char			*ft_convert_hexa_l(uintmax_t hex, char *str)
{
	int			i;
	uintmax_t	restl;

	i = 0;
	while (hex > 0)
	{
		restl = hex % 16;
		if (restl < 10)
			str[i] = restl + 48;
		else
			str[i] = restl + 87;
		hex = hex / 16;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char			*ft_convert_hexa(t_stock *stock, int j, t_struct *stru,
		uintmax_t hex)
{
	char		*str;

	if (!(str = (char*)malloc(sizeof(char) * 17)))
		return (0);
	if (stock->stock_il == 0 && (stru->indic == 'x' || stru->indic == 'X'))
		return (pf_strdup("0"));
	if (j == 0)
		str = ft_convert_hexa2(stock, str);
	else
		str = ft_convert_hexa_l(hex, str);
	str = pf_strrev(str);
	return (str);
}

static void			ft_indic_x2(t_struct *stru, t_stock *stock)
{
	if (stru->indic == 'x' || stru->indic == 'p')
	{
		stock->stock_s = ft_convert_hexa(stock, 1, stru, stock->stock_il);
		ft_indic_s(stru, stock);
	}
	else
	{
		stock->stock_s =
			ft_toupper_mod(ft_convert_hexa(stock, 1, stru, stock->stock_il));
		ft_indic_s(stru, stock);
	}
}

void				ft_indic_x(t_struct *stru, t_stock *stock)
{
	if (stru->flag[8] == 0 && stru->flag[7] == 0)
	{
		if (stru->flag[5] == 1)
			stock->stock_h = 256;
		else if (stru->flag[6] == 1)
			stock->stock_h = 65536;
		else
			stock->stock_h = 4294967296;
		if (stock->stock_il < 0)
			stock->stock_il = stock->stock_il % stock->stock_h + stock->stock_h;
		if (stru->indic == 'x')
		{
			stock->stock_s = ft_convert_hexa(stock, 0, stru, 0);
			ft_indic_s(stru, stock);
		}
		else
		{
			stock->stock_s =
				ft_toupper_mod(ft_convert_hexa(stock, 0, stru, 0));
			ft_indic_s(stru, stock);
		}
	}
	else
		ft_indic_x2(stru, stock);
}
