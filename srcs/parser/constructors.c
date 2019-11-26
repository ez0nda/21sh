/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:33:47 by ezonda            #+#    #+#             */
/*   Updated: 2019/11/26 02:38:08 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_cmd	*parse_basic_cmd(void)
{
	t_exec_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = BASIC;
//	ft_printf("\nPARSE BASIC\n");
//	getchar();
	return (t_cmd*)cmd;
}

t_cmd	*parse_redir_cmd(
	t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redirection_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
//	ft_printf("\nPARSE REDIR - file : {%s}\n", file);
	cmd->file = rm_char(file, ' ');
	cmd->mode = mode;
//	ft_printf("\nPARSE REDIR - file : {%s}\n", file);
//	getchar();
	cmd->fd = fd;
	return (t_cmd*)cmd;
}

t_cmd	*parse_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (t_cmd*)cmd;
}
