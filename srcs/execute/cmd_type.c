/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:57:19 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/23 16:51:57 by ezonda           ###   ########.fr       */
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
}

int			check_cmd(t_var *data)
{
	char	**split;

	split = ft_strsplit(data->cmds[data->cmd_index], ' ');
	if (split[0][0] == '<' && split[0][1] == '<')
	{
		free_tab(split);
		return (0);
	}
	else
	{
		if (!ft_strcmp(split[0], "cat"))
			data->cat_here = 1;
		else
			data->cat_here = 0;
		free_tab(split);
		return (1);
	}
}

int			is_aggreg(char *file)
{
	if (!strcmp(file, "&0") || !strcmp(file, "&1") || !ft_strcmp(file, "&2"))
		return (1);
	return (0);
}

void		restore_fd(t_var *data, int new_fd, t_redirection_cmd *rcmd)
{
	int back_fd;

	if (new_fd == -1)
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putendl_fd(rcmd->file, 2);
		free(rcmd->file);
		return ;
	}
	back_fd = dup(rcmd->fd);
	dup2(new_fd, rcmd->fd);
	close(new_fd);
	get_cmd_type(rcmd->cmd, data);
	dup2(back_fd, rcmd->fd);
	free(rcmd->file);
}

void		cmd_redir(t_cmd *cmd, t_var *data)
{
	t_redirection_cmd	*rcmd;
	int					new_fd;

	rcmd = (t_redirection_cmd *)cmd;
	if (rcmd->mode == 524)
	{
		ft_putchar('\n');
		data->herend = ft_strdup(rm_char(rcmd->file, ' '));
		heredoc_prompt(data);
//		ft_printf("\ncmd2 : |%s|\n", data->cmds[data->cmd_index]);
		if (!check_cmd(data))
		{
			free(rcmd->file);
			return ;
		}
	}
	else if (rcmd->mode != 516 && rcmd->mode != 524 && !is_aggreg(rcmd->file))
	{
		if (!ft_strcmp(rcmd->file, "&-"))
			rcmd->file = ft_strdup("/dev/null");
		new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
		add_to_files(data, rcmd->file);
	}
	else if (rcmd->mode == 516)
	{
		ft_putchar('\n');
		new_fd = open(rcmd->file, O_RDONLY);
	}
	restore_fd(data, new_fd, rcmd);
}

int			is_cat_heredoc(t_var *data)
{
	if (data->cat_here)
	{
		data->cat_here = 0;
		ft_putstr(data->here_stock);
		ft_bzero(data->here_stock, ft_strlen(data->here_stock));
		free_tab(data->argv);
		ft_putchar('\n');
		return (1);
	}
	return (0);
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
		return ;
	init_exec(data);
	free_tab(data->argv);
}

void		get_cmd_type(t_cmd *cmd, t_var *data)
{
	int		i;

	i = 0;
	while (is_whitespaces(data->cmds[data->cmd_index][i]) 
			|| is_pipe(data->cmds[data->cmd_index][i]))
		i++;
	if (i == ft_strlen(data->cmds[data->cmd_index]))
	{
		ft_putchar('\n');
		return ;
	}
	if (cmd->type == PIPE)
	{
		cmd_pipe(cmd, data);
//	free(&cmd->type);
	}
	else if (cmd->type == REDIR)
	{
		cmd_redir(cmd, data);
//	free(&cmd->type);
	}
	else if (cmd->type == BASIC)
	{
		cmd_basic(cmd, data);
//	free_tab(cmd);
	}
}
