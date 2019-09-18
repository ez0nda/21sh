/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:44:52 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/18 13:33:48 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void		execute(char **bin_path, char **cmd, pid_t father, t_var *data)
{
	int		i;
	char	*path;

	i = 0;
	if (bin_path != NULL)
	{
		while (bin_path[i])
		{
			if (cmd[0][0] != '/' && cmd[0][0] != '.')
				path = init_path(bin_path[i], cmd[0]);
			else
				path = ft_strdup(cmd[0]);
			if (access(path, X_OK) != -1 && father == 0)
				execve(path, cmd, data->environ);
			free(path);
			i++;
		}
	}
	else
	{
		if (access(cmd[0], X_OK) != -1 && father == 0)
			execve(cmd[0], cmd, data->environ);
	}
}

void			exec_cmd(char **bin_path, char **lexer, t_var *data)
{
	int		i;
	pid_t	father;

	i = 0;
	while (data->lexer[i])
	{
		if (data->lexer[i][0] == '$')
			data->lexer[i] = get_dollar_var(lexer[i], data);
		i++;
	}
//	int j = 0;
//	while (lexer[j])
//		ft_printf("\ncmd : %s\n", lexer[j++]);
	father = fork();
	execute(bin_path, lexer, father, data);
	if (father == 0)
	{
		if (lexer[0][0] != '\n')
			error_msg(bin_path,/* lexer[0]*/data->lex_str);
		exit(1);
	}
	if (father > 0)
		wait(NULL);
}
