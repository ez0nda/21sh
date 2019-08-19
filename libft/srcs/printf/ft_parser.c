/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 09:59:40 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/02 15:01:01 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_find_indicator(const char *format, t_struct *stru)
{
	int		i;

	i = 0;
	ft_initialize_flags(stru);
	while (format[i] != 'd' && format[i] != 'i' && format[i] != 'o' &&
			format[i] != 'u' && format[i] != 'x' && format[i] != 'X' &&
			format[i] != 'c' && format[i] != 's' && format[i] != 'p' &&
			format[i] != 'f' && format[i] != '%' && format[i] != 'U')
		i++;
	stru->indic = format[i];
	if (ft_check_format(format, stru) == 0)
		return (0);
	return (1);
}

void	ft_check_flags(const char *format, t_struct *stru, t_stock *stock)
{
	int i;

	i = 0;
	while (format[i] != 'd' && format[i] != 'i' && format[i] != 'o' &&
			format[i] != 'u' && format[i] != 'x' && format[i] != 'X' &&
			format[i] != 'c' && format[i] != 's' && format[i] != 'p' &&
			format[i] != 'f' && format[i] != '%')
	{
		if (format[i] == '0' && (format[i - 1] < '0' || format[i - 1] > '9')
				&& format[i - 1] != '.')
			stru->flag[0] = 1;
		if (format[i] == '#')
			stru->flag[1] = 1;
		if (format[i] == '-')
			stru->flag[2] = 1;
		if (format[i] == '+')
			stru->flag[3] = 1;
		if (format[i] == ' ')
			stru->flag[4] = 1;
		if (format[i] == '*')
			stru->min_field = va_arg(stru->ap, int);
		i = ft_check_flags_p2(format, stru, i);
	}
	ft_stock(stock, stru);
	ft_dispatch(stru, stock);
}

int		ft_check_flags_p2(const char *format, t_struct *stru, int i)
{
	if (format[i] == 'h' && format[i + 1] == 'h')
		stru->flag[5] = 1;
	else if (format[i] == 'h' && format[i + 1] != 'h')
		stru->flag[6] = 1;
	if (format[i] == 'l' && format[i + 1] == 'l')
		stru->flag[7] = 1;
	else if (format[i] == 'l' && format[i + 1] != 'l')
		stru->flag[8] = 1;
	if (format[i] == 'L')
		stru->flag[9] = 1;
	i++;
	return (i);
}

void	ft_check_width(const char *format, t_struct *stru)
{
	int		i;
	int		j;
	char	*width;

	i = 0;
	j = 0;
	width = pf_strnew(0);
	while (format[i] != stru->indic && format[i] != '.')
	{
		if (pf_isdigit(format[i]) && format[i] != stru->indic)
		{
			width[j] = format[i];
			j++;
		}
		i++;
		width[j] = '\0';
	}
	stru->min_field = pf_atoi(width);
	free(width);
}

void	ft_check_precision(const char *format, t_struct *stru)
{
	int		i;
	int		j;
	char	*pre;

	i = 0;
	j = 0;
	pre = pf_strnew(0);
	stru->prec = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '.')
		{
			stru->flag[10] = 1;
			while (pf_isdigit(format[++i]))
				pre[j++] = format[i];
			i--;
		}
		i++;
		pre[j] = '\0';
		if (format[i] == stru->indic)
			break ;
	}
	stru->prec = pf_atoi(pre);
	free(pre);
}
