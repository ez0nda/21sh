/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 13:36:39 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/31 20:00:52 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_invalid(const char *format, t_struct *stru)
{
	int i;

	i = 0;
	while (format[i] == ' ')
		i++;
	pf_putstr(&format[i], stru);
}

int		ft_check_format(const char *format, t_struct *stru)
{
	int i;

	i = 0;
	stru->valid = 0;
	while (format[i] == '0' || format[i] == '#' || format[i] == '+'
			|| format[i] == '-' || format[i] == ' ' || format[i] == '.'
			|| format[i] == 'h' || format[i] == 'l' || format[i] == 'L'
			|| format[i] == 'j' || format[i] == 'z' || pf_isdigit(format[i])
			|| format[i] == '*')
		i++;
	while (format[stru->valid] != stru->indic)
		stru->valid++;
	if (i == stru->valid)
		return (1);
	else
	{
		ft_invalid(format, stru);
		return (0);
	}
}

void	ft_dispatch(t_struct *stru, t_stock *stock)
{
	if (stru->indic == 'c')
		ft_indic_c(stru, stock);
	if (stru->indic == 's')
		ft_indic_s(stru, stock);
	if (stru->indic == 'p')
		ft_indic_p(stru, stock);
	if (stru->indic == 'd' || stru->indic == 'i')
		ft_indic_di(stru, stock);
	if (stru->indic == 'o')
		ft_indic_o(stru, stock);
	if (stru->indic == 'u' || stru->indic == 'U')
		ft_indic_u(stru, stock);
	if (stru->indic == 'x' || stru->indic == 'X')
		ft_indic_x(stru, stock);
	if (stru->indic == 'f')
		ft_indic_f(stru, stock);
	if (stru->indic == '%')
		ft_indic_mod(stru);
}

void	ft_stock(t_stock *stock, t_struct *stru)
{
	if ((stru->indic == 'd' || stru->indic == 'i')
			&& stru->flag[7] == 0 && stru->flag[8] == 0)
		stock->stock_i = va_arg(stru->ap, int);
	else if (((stru->indic == 'o' || stru->indic == 'u' || stru->indic == 'U'
			|| stru->indic == 'x' || stru->indic == 'X' || stru->indic == 'p')
			&& (stru->flag[8] == 0 && stru->flag[7] == 0)))
		stock->stock_il = va_arg(stru->ap, long);
	else if ((stru->indic == 'd' || stru->indic == 'i') && (stru->flag[8] == 1
			|| stru->flag[7] == 1))
		stock->stock_il = va_arg(stru->ap, long);
	else if ((stru->indic == 'u' || stru->indic == 'x' || stru->indic == 'X'
			|| stru->indic == 'o') && (stru->flag[8] == 1
			|| stru->flag[7] == 1))
		stock->stock_il = (intmax_t)va_arg(stru->ap, long);
	if (stru->indic == 'c')
		stock->stock_c = (char)va_arg(stru->ap, int);
	if (stru->indic == 's')
		if (!(stock->stock_s = va_arg(stru->ap, char*)))
			return ;
	if (stru->indic == 'f')
		stock->stock_f = va_arg(stru->ap, double);
	stock->stock_free = pf_itoa(stock->stock_il);
	stru->modl = pf_strcmp(stock->stock_free, "-9223372036854775808")
		== 0 ? 0 : 1;
	free(stock->stock_free);
}

void	ft_initialize_flags(t_struct *stru)
{
	int i;

	i = 0;
	stru->stock_pre2 = 0;
	while (i <= 10)
	{
		stru->flag[i] = 0;
		i++;
	}
}
