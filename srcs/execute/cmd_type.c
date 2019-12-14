/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:57:19 by ezonda            #+#    #+#             */
/*   Updated: 2019/12/14 11:24:19 by ezonda           ###   ########.fr       */
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
	if (!ft_strcmp(split[0], "<<"))
		return (0);
	else
	{
		if (!ft_strcmp(split[0], "cat"))
			data->cat_here = 1;
		else
			data->cat_here = 0;
		return (1);
	}
}

int			count_redir(t_var *data)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == '>' && data->lex_str[i] + 1 != '>')
			count++;
		i++;
	}
	return (count);
}
/*
void	test(t_var *data, t_cmd *cmd)
{
	int i;
	t_redirection_cmd	*rcmd;

	i = 0;
	rcmd = (t_redirection_cmd *)cmd;
//	ft_printf("\nfile : {%s} - fd : %d\n", rcmd->file, rcmd->fd);
	data->redir_count++;
	data->argv = (char**)malloc(sizeof(char*) * 2);
	if (data->redir_count == data->test)
	{
//		ft_putendl_fd("\nlast redir", 0);
//		getchar();
		return ;
	}
	while (data->cmds[data->cmd_index][i]
			&& data->cmds[data->cmd_index][i] != '>')
	{
		add_to_here_stock(data->cmds[data->cmd_index][i], data);
		i++;
	}
//	ft_printf("\nstock : {%s}\n", data->here_stock);
	data->argv[0] = ft_strdup(rm_char(data->here_stock, ' '));
	data->argv[1] = NULL;
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	init_exec(data);
//	ft_putendl_fd("\nout test", 0);
//	getchar();
//	get_cmd_type(rcmd->cmd, data);
}
*/
void		cmd_redir(t_cmd *cmd, t_var *data)
{
	t_redirection_cmd	*rcmd;
	int					count;
	int					new_fd;
	int					back_fd;

	rcmd = (t_redirection_cmd *)cmd;
	count = count_redir(data);
	data->test = count_redir(data);
	if (rcmd->mode == 524)
	{
		ft_putchar('\n');
		data->herend = ft_strdup(rm_char(rcmd->file, ' '));
		heredoc_prompt(data);
		if (!check_cmd(data))
			return ;
	}
	else if (rcmd->mode != 516 && rcmd->mode != 524)
	{
		new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
		add_to_files(data, rcmd->file);
	}
	else if (rcmd->mode == 516)
		new_fd = open(rcmd->file, O_RDONLY);
	if (new_fd == -1)
	{
		ft_putstr_fd("\n21sh: no such file or directory: ", 2);
		ft_putendl_fd(rcmd->file, 2);
		return ;
	}
	back_fd = dup(rcmd->fd);
	dup2(new_fd, rcmd->fd);
	close(new_fd);
	get_cmd_type(rcmd->cmd, data);
	dup2(back_fd, rcmd->fd);
}

void		cmd_basic(t_cmd *cmd, t_var *data)
{
	int			i;
	char		**split;
	t_list		*cur;
	t_exec_cmd	*ecmd;

	i = 0;
	ecmd = (t_exec_cmd *)cmd;
	data->argv = malloc(sizeof(char*) * (ft_lstcount(ecmd->argv) + 1));
	cur = ecmd->argv;
	while (cur)
	{
		data->argv[i] = cur->content;
		cur = cur->next;
		i++;
	}
	data->argv[i] = NULL;
	if (data->cat_here)
	{
		data->cat_here = 0;
		ft_putstr(data->here_stock);
		ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	}
	i = 0;
	init_exec(data);
}

void		get_cmd_type(t_cmd *cmd, t_var *data)
{
	int		i;
	char	*path;
	char	**bin_path;

	i = 0;
	while (is_whitespaces(data->cmds[data->cmd_index][i]))
		i++;
	if (i == ft_strlen(data->cmds[data->cmd_index]))
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
