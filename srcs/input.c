/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:12:15 by ezonda            #+#    #+#             */
/*   Updated: 2019/08/19 14:02:06 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

void	get_input(t_var *data)
{
	char buffer[6];

	ft_putstr("21sh-$> ");
	while (1)
	{
		update_data(0, data);
		ft_bzero(buffer, 6);
		read(0, &buffer, sizeof(buffer));
		if (ft_isalnum(buffer[0]) && buffer[1] == 0)
		{
			ft_putchar(buffer[0]);
			data->pos++;
		}
		ft_printf("%d\n", data->pos);
/*		ft_printf("%d ", buffer[0]);
		ft_printf("%d ", buffer[1]);
		ft_printf("%d ", buffer[2]);
		ft_printf("%d ", buffer[3]);
		ft_printf("%d ", buffer[4]);
		ft_printf("%d\n", buffer[5]);*/
	}
}
