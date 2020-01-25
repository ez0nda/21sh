/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 09:50:07 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/12 14:47:02 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void		restore_fd(t_var *data, int new_fd, t_redirection_cmd *rcmd)
{
//	int back_fd;

	if (new_fd == -1)
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putendl_fd(rcmd->file, 2);
		free(rcmd->file);
		free(rcmd);
		return ;
	}
	data->back_fd = dup(rcmd->fd);
	dup2(data->new_fd, rcmd->fd);
	close(new_fd);
//	ft_printf("\nHERE\n");
//	getchar();
	if (rcmd->cmd->type == REDIR)
		data->in_redir = 1;
	get_cmd_type(rcmd->cmd, data);
	dup2(data->back_fd, rcmd->fd);
	free(rcmd->file);
	free(rcmd);
	data->in_redir = 0;
}

void		init_heredoc_fd(t_var *data, t_redirection_cmd *rcmd, int mod)
{
	if (!mod)
	{
		dup2(data->back_fd, 1);
		close(data->new_fd);
//		data->back_fd = dup(rcmd->fd);
//		data->new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
	}
}

void		free_pipe(t_pipe_cmd *pcmd)
{
	t_exec_cmd		*ecmd_left;
	t_exec_cmd		*ecmd_right;

	ecmd_left = (t_exec_cmd *)pcmd->left;
	ecmd_right = (t_exec_cmd *)pcmd->right;

	free(ecmd_left->argv->content);
	free(ecmd_right->argv->content);

	free_lst(ecmd_left->argv);
	free_lst(ecmd_right->argv);

	free(pcmd->left);
	free(pcmd->right);

	free(pcmd);
}

void		cmd_pipe(t_cmd *cmd, t_var *data)
{
	t_pipe_cmd		*pcmd;
	int			pipes[2];
	int			pid[2];

	data->pipe = 1;
	pcmd = (t_pipe_cmd *)cmd;
	if (pipe(pipes) != 0)
		ft_putendl_fd("\n21sh: pipe: syntax error", 2);
	else if ((pid[0] = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		get_cmd_type(pcmd->left, data);
		exit(0);
	}
	if ((pid[1] = fork()) == 0)
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
	free_pipe(pcmd);
	data->pipe = 0;
}

void		cmd_redir(t_cmd *cmd, t_var *data)
{
	t_redirection_cmd	*rcmd;
//	int					new_fd;

//	data->new_fd = 0;
	rcmd = (t_redirection_cmd *)cmd;
	if (data->in_redir != 1)
		data->rfile = ft_strdup(rcmd->file);
	if (rcmd->mode == (O_RDONLY | O_NONBLOCK | O_CREAT | O_APPEND))
	{
		if (data->in_redir == 1)
		{
			init_heredoc_fd(data, rcmd, 0);
		}
		if (!init_heredoc(data, rcmd))
			return ;
	}
	else if (rcmd->mode != (O_RDONLY | O_NONBLOCK | O_CREAT)
			&& rcmd->mode != (O_RDONLY | O_NONBLOCK | O_CREAT | O_APPEND)
			&& !is_aggreg(rcmd->file))
	{
		if (!ft_strcmp(rcmd->file, "&-"))
			rcmd->file = close_fd(rcmd->file);
		data->new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
	}
	else if (rcmd->mode == (O_RDONLY | O_NONBLOCK | O_CREAT))
	{
		ft_putchar('\n');
		data->new_fd = open(rcmd->file, O_RDONLY);
	}
	restore_fd(data, data->new_fd, rcmd);
}

void		cmd_basic(t_cmd *cmd, t_var *data)
{
	int			i;
	t_list		*cur;
	t_exec_cmd	*ecmd;

	i = 0;
	ecmd = (t_exec_cmd *)cmd;
	if (!(data->argv =
				(char**)malloc(sizeof(char*) * (ft_lstcount(ecmd->argv) + 1))))
		return ;
	cur = ecmd->argv;
	while (cur)
	{
		data->argv[i] = cur->content;
		cur = cur->next;
		i++;
	}
	data->argv[i] = NULL;
	if (is_cat_heredoc(data))
	{
		free(ecmd->argv);
		free(ecmd);
		return ;
	}
	init_exec(data);
	free_tab(data->argv);
	ft_strdel(&data->here_stock);
	if (!data->pipe) 				// n'a aucun effet
	{
//		ft_printf("\n\nFREE LST + CMD\n");
		free_lst(ecmd->argv);
		free(ecmd);
	}
}

void		get_cmd_type(t_cmd *cmd, t_var *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(data->cmds[data->cmd_index]);
	while (is_whitespaces(data->cmds[data->cmd_index][i])
			|| is_pipe(data->cmds[data->cmd_index][i]))
		i++;
	if (i == len)
	{
		ft_putchar('\n');
		return ;
	}
	if (cmd->type == PIPE)
	{
//		ft_printf("\nPIPE\n");
		cmd_pipe(cmd, data);
	}
	else if (cmd->type == REDIR)
	{
//		ft_printf("\nREDIR\n");
		cmd_redir(cmd, data);
	}
	else if (cmd->type == BASIC)
	{
//		ft_printf("\nCMD\n");
		cmd_basic(cmd, data);
	}
}
