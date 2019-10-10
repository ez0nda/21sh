/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:57:19 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/10 14:53:13 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void		cmd_pipe(t_cmd *cmd, t_var *data)
{
	t_pipe_cmd		*pcmd;
	int				pipes[2];
	int				pid[2];

	pcmd = (t_pipe_cmd *)cmd;
	if (pipe(pipes) != 0)
		ft_putendl_fd("pipe error", 2);
	else if ((pid[0] = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		get_cmd_type(pcmd->left, data);
		exit(0);
	}
	ft_printf("\nHERE\n");
	if ((pid[1] == fork()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		get_cmd_type(pcmd->right, data);
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
}

void		cmd_redir(t_cmd *cmd, t_var *data)
{
	t_redirection_cmd	*rcmd;
	int					new_fd;
	int					back_fd;

	rcmd = (t_redirection_cmd *)cmd;
	new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
	back_fd = dup(rcmd->fd);
	dup2(new_fd, rcmd->fd);
	close(new_fd);
	get_cmd_type(rcmd->cmd, data);
	dup2(back_fd, rcmd->fd);
	ft_putchar('\n');
}

void		cmd_basic(t_cmd *cmd, t_var *data)
{
	t_list *cur;
	t_exec_cmd *ecmd;
	int i;

	ecmd = (t_exec_cmd *)cmd;
	data->argv = malloc(sizeof(char*) * (ft_lstcount(ecmd->argv) + 1));
	i = 0;
	cur = ecmd->argv;
	while (cur && ft_strcmp(cur->content, ";"))
	{
		data->argv[i] = cur->content;
		i++;
		cur = cur->next;
	}
	data->argv[i] = NULL;
	init_exec(data);
}

void		get_cmd_type(t_cmd *cmd, t_var *data)
{
	int i;
	char *path;
	char **bin_path;

	i = 0;
	while (is_whitespaces(data->lex_str[i]))
		i++;
	if (i == ft_strlen(data->lex_str))
	{
		ft_putchar('\n');
		return;
	}
	path = get_var("PATH=", data->environ);
	bin_path = ft_strsplit(path, ':');
	if (cmd->type == PIPE)
		cmd_pipe(cmd, data);
	else if (cmd->type == REDIR)
		cmd_redir(cmd, data);
	else if (cmd->type == BASIC)
		cmd_basic(cmd, data);
}
