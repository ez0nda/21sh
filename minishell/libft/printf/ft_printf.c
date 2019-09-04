/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 09:05:54 by ezonda            #+#    #+#             */
/*   Updated: 2019/01/31 20:24:49 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_struct	stru;
	t_stock		stock;

	va_start(stru.ap, format);
	stru.index = 0;
	stru.count_char = 0;
	while (format[stru.index] != '\0')
	{
		if (format[stru.index] == '%')
		{
			stru.index++;
			if (ft_find_indicator(&format[stru.index], &stru) == 0)
				return (stru.count_char);
			ft_check_width(&format[stru.index], &stru);
			ft_check_precision(&format[stru.index], &stru);
			ft_check_flags(&format[stru.index], &stru, &stock);
			while (format[stru.index] != stru.indic)
				stru.index++;
		}
		else if (format[stru.index] != '%')
			pf_putchar(format[stru.index], &stru);
		stru.index++;
	}
	va_end(stru.ap);
	return (stru.count_char);
}
