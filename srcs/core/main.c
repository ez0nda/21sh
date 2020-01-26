/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:34:31 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 14:16:15 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

t_var	*update_data(int mod, t_var *data)
{
	static t_var *data2;

	if (mod == 0)
		data2 = data;
	return (data2);
}

int		main(int ac, char **av, char **env)
{
	t_var data;

	ft_memset(&data, 0, sizeof(t_var));
	if (!env || !*env)
		set_env(&data);
	else
		data.environ = ft_tabdup(env, 0);
	signal_handler();
	init_shell(&data);
	manage_history(&data);
	set_termcanon(&data);
	if (ac == 1 && av[0] != NULL)
		get_input(&data);
	else
		ft_putendl_fd("21sh: too many arguments\nusage: ./21sh", 2);
	return (exit_shell(&data));
}
