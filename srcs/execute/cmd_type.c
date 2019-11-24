/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:57:19 by ezonda            #+#    #+#             */
/*   Updated: 2019/11/24 01:59:21 by ezonda           ###   ########.fr       */
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
//		ft_printf("\nget type left1\n");
//		ft_printf("\npipe0 : %d - pipe1 : %d\n", pipes[0], pipes[1]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
//		ft_printf("\nget type left2\n");
		get_cmd_type(pcmd->left, data);
		exit(0);
	}
	if ((pid[1] = fork()) == 0)
	{
//		ft_printf("\nget type right1\n");
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
//		ft_printf("\nget type right2\n");
		get_cmd_type(pcmd->right, data);
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
}

void		add_to_here_stock(char c, t_var *data)
{
	int i;

	i = 0;
	while (data->here_stock[i])
		i++;
	data->here_stock[i++] = c;
	data->here_stock[i] = '\0';
}

void		rm_herend(t_var *data)
{
	int i;

	i = ft_strlen(data->here_stock);
	while (data->here_stock[i] != '\n')
	{
		data->here_stock[i] = '\0';
		i--;
	}
	data->here_stock[i] = '\0';
}

void		heredoc_read(t_var *data)
{
	char buffer[6];

	data->h_prompt = 1;
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	while (1)
	{
		prompt(data);
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if ((buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0))
		{
			ft_putchar(buffer[0]);
			add_to_here_stock(buffer[0], data);
			data->lex_str = ft_strjoin(data->lex_str, &buffer[0]);
			data->pos = ft_strlen(data->lex_str);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			ft_putchar('\n');
			if (!ft_strcmp(data->lex_str, data->herend))
			{
				rm_herend(data);
				break ;
			}
			add_to_here_stock('\n', data);
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
		}
		get_key(data, buffer);
	}
	ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	data->h_prompt = 0;
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

char		*rm_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
			i = 0;
		}
		i++;
	}
	return (str);
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
//	ft_printf("\ncount : %d\n", count);
	return (count);
}

void		add_to_files(t_var *data, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->files[i])
		i++;
	while (str[j])
	{
		data->files[i] = str[j];
		i++;
		j++;
	}
	data->files[i++] = ' ';
	data->files[i] = '\0';
}

void		update_files(t_var *data)
{
	int		fd;
	int		back_fd;
	char	*line;
	char	**split;

	split = ft_strsplit(data->files, ' ');
	fd = open(split[0], O_RDONLY, O_APPEND);
	back_fd = dup(1);
	dup2(fd, 1);
}

void		cmd_redir(t_cmd *cmd, t_var *data)
{
	t_redirection_cmd	*rcmd;
	int					count;
	int					new_fd;
	int					back_fd;

//	if (!data->test)
//	ft_printf("\ntest : %d\n", test);
//	if (count == test)
//	{
//		ft_printf("\nRETURN\n");
//		return ;
//	}
	rcmd = (t_redirection_cmd *)cmd;
	ft_putstr_fd("\nredir start - file : ", 0);
	ft_putendl_fd(rcmd->file, 0);
	getchar();
//	ft_printf("\nfile[0] : {%c}\n", rcmd->file[0]);
//	getchar();
	count = count_redir(data);
	if (rcmd->mode == 524)
	{
		ft_putchar('\n');
		data->herend = ft_strdup(rm_char(rcmd->file, ' '));
		heredoc_read(data);
		if (!check_cmd(data))
			return ;
	}
	else if (rcmd->mode != 516 && rcmd->mode != 524)
	{
//		ft_putstr_fd("\nout dup\n", 0);
//		getchar();
		//get_cmd_type(rcmd->cmd, data);
		new_fd = open(rcmd->file, rcmd->mode, S_IRUSR | S_IWUSR);
		add_to_files(data, rcmd->file);
//		cmd_redir(rcmd->cmd, data);
//		ft_printf("\nnew file : {%s} -%d-\n", rcmd->file, count++);


	//	if (count == test)
	//		return ;
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
	ft_putstr_fd("\nin dup\n", 0);
	getchar();
	get_cmd_type(rcmd->cmd, data);
	dup2(back_fd, rcmd->fd);
//	if (count > 1)
//		update_files(data);
	ft_putstr_fd("\nredir end - file : ", 0);
	ft_putendl_fd(rcmd->file, 0);
	getchar();
}

void		cmd_basic(t_cmd *cmd, t_var *data)
{
	int			i;
	char		**split;
	t_list		*cur;
	t_exec_cmd	*ecmd;

	ft_putstr_fd("\nbasic start\n", 0);
	getchar();
	i = 0;
	ecmd = (t_exec_cmd *)cmd;
	data->argv = malloc(sizeof(char**) * (ft_lstcount(ecmd->argv) + 1));
//	data->argv = (char**)malloc(sizeof(char*) * BUFF_SHELL);
	cur = ecmd->argv;
	while (cur)
	{
		data->argv[i] = cur->content;
	//	ft_printf("\nargv: %s\n", cur->content);
		cur = cur->next;
		i++;
	}
	data->argv[i] = NULL;
//	split = ft_strsplit(data->cmds[data->cmd_index], ' ');
//	while (split[i])
//	{
//		data->argv[i] = ft_strdup(split[i]);
//		i++;
//	}
//	data->argv[i] = NULL;
	if (data->cat_here)
	{
		data->cat_here = 0;
		ft_putstr(data->here_stock);
		ft_bzero(data->here_stock, ft_strlen(data->here_stock));
	}
	i = 0;
//	while (data->argv[i])
//		ft_printf("\nargv[i]: {%s}\n", data->argv[i++]);
	init_exec(data);
	ft_putstr_fd("\nbasic end\n", 0);
	getchar();
}

void		get_cmd_type(t_cmd *cmd, t_var *data)
{
	int		i;
	char	*path;
	char	**bin_path;

	ft_putstr_fd("\ngcmd start\n", 0);
	getchar();
	i = 0;
//	ft_printf("\n\nin cmd_type\n\n");
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
	{
//		if (cmd->single_pipe == 1)
//			ft_printf("\nSINGLE PIPE\n");
		cmd_pipe(cmd, data);
	}
	else if (cmd->type == REDIR)
	{
		ft_putstr_fd("\nREDIR\n", STDIN_FILENO);
		getchar();
		cmd_redir(cmd, data);
	}
	else if (cmd->type == BASIC)
	{
		ft_putstr_fd("\nBASIC\n", STDIN_FILENO);
		getchar();
		cmd_basic(cmd, data);
	}
	ft_putstr_fd("\ngcmd end\n", 0);
	getchar();
//	else
//		ft_printf("\nNO CMD\n");
}
