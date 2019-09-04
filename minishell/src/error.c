/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:04:27 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/06 15:45:58 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl(int signal)
{
	char *path;

	(void)signal;
	write(0, "\n", 1);
	path = get_pwd();
	ft_printf("[%s]-> ", path);
}

void	print_error(char *buf)
{
	int i;

	i = ft_strlen(buf);
	i--;
	buf[i] = '\0';
	ft_printf("%s: Commande introuvable\n", buf);
}

int		error_env(void)
{
	ft_putstr_fd("environment not found\n", 2);
	return (-1);
}

void	error_path(int mod, char *line)
{
	if (mod == 0)
		ft_putstr_fd("PATH not found\n", 2);
	else if (mod == 1)
		ft_printf("%s: permission denied\n", line);
	exit(1);
}

int		error_cd(char *str, int mod)
{
	if (mod == 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (mod == 1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (mod == 2)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	free(str);
	return (-1);
}
