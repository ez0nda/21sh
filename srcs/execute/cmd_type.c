/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:57:19 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/05 13:24:55 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void		restore_fd(t_var *data, int new_fd, t_redirection_cmd *rcmd)
{
	int back_fd;

	if (new_fd == -1)
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putendl_fd(rcmd->file, 2);
		free(rcmd->file);
		free(rcmd);
		return ;
	}
	back_fd = dup(rcmd->fd);
	dup2(new_fd, rcmd->fd);
	close(new_fd);
	get_cmd_type(rcmd->cmd, data);
	dup2(back_fd, rcmd->fd);
//	ft_printf("\nREDIR FREE\n");
	free(rcmd->file);
	free(rcmd);
}

void		cmd_pipe(t_cmd *cmd, t_var *data)
{
	t_pipe_cmd		*pcmd;
	int				pipes[2];
	int				pid[2];

	pcmd = (t_pipe_cmd *)cmd;
	if (pipe(pipes) != 0)
		ft_putendl_fd("\n21sh: pipe: syntax error", 2);
	else if ((pid[0] = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		get_cmd_type(pcmd->left, data);
//		ft_printf("\nPIPE FREE in fork 0\n");
		exit(0);
	}
	if ((pid[1] = fork()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		get_cmd_type(pcmd->right, data);
//		ft_printf("\nPIPE FREE in fork 1\n");
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
//	ft_printf("\nPIPE FREE no fork\n");
}

void		cmd_redir(t_cmd *cmd, t_var *data)
{
	t_redirection_cmd	*rcmd;
	int					new_fd;

	new_fd = 0;
	rcmd = (t_redirection_cmd *)cmd;
	if (rcmd->mode == (O_RDONLY | O_NONBLOCK | O_CREAT | O_APPEND))
	{
		if (!init_heredoc(data, rcmd))
		{
			return ;
		}
	}
	else if (rcmd->mode != (O_RDONLY | O_NONBLOCK | O_CREAT)
			&& rcmd->mode != (O_RDONLY | O_NONBLOCK | O_CREAT | O_APPEND)
			&& !is_aggreg(rcmd->file))
	{
		if (!ft_strcmp(rcmd->file, "&-"))
			rcmd->file = ft_strdup("/dev/null");
		new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
	}
	else if (rcmd->mode == (O_RDONLY | O_NONBLOCK | O_CREAT))
	{
		ft_putchar('\n');
		new_fd = open(rcmd->file, O_RDONLY);
	}
	restore_fd(data, new_fd, rcmd);
}

void		cmd_basic(t_cmd *cmd, t_var *data)
{
	int			i;
	char		**split;
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
//	ft_printf("\nCMD + LST FREE\n");
	free(ecmd->argv);
	free(ecmd);
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
		cmd_pipe(cmd, data);
	else if (cmd->type == REDIR)
		cmd_redir(cmd, data);
	else if (cmd->type == BASIC)
		cmd_basic(cmd, data);
}
