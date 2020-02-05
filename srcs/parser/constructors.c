/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:33:47 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/05 13:27:06 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_cmd	*parse_basic_cmd(void)
{
	t_exec_cmd *cmd;

//	ft_printf("\nCMD MALLOC\n");
	cmd = malloc(sizeof(*cmd));
	cmd->type = BASIC;
	return (t_cmd*)cmd;
}

t_cmd	*parse_redir_cmd(
	t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redirection_cmd *cmd;

//	ft_printf("\nREDIR MALLOC\n");
	cmd = malloc(sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = ft_strdup(rm_char(file, ' '));
	free(file);
	cmd->mode = mode;
	cmd->fd = fd;
	return (t_cmd*)cmd;
}

t_cmd	*parse_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd *cmd;

//	ft_printf("\nPIPE MALLOC\n");
	cmd = malloc(sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (t_cmd*)cmd;
}
