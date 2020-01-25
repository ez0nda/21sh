/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:59:19 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/12 14:55:34 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

char		*close_fd(char *file)
{
	free(file);
	file = ft_strdup("/dev/null");
	return (file);
}

void		add_dollar(t_var *data)
{
	int i;

	i = 0;
	while (data->here_stock[i])
	{
		while (data->here_stock[i] || data->here_stock[i] != '\n')
			i++;
		data->here_stock[i++] = '$';
		data->here_stock[i] = '\n';
		i++;
	}
}

void		test_fd_heredoc(t_var *data, int mod)
{
	int new_fd;
	int back_fd;

	ft_printf("\nFILE : %s\n", data->rfile);
	new_fd = open(data->rfile, O_WRONLY, O_APPEND);
	if (mod == 1)
	{
		back_fd = dup(1);
		dup2(new_fd, 1);
		ft_putstr(data->here_stock);
		close(new_fd);
		dup2(new_fd, back_fd);
		dup2(data->back_fd, data->new_fd);
	}
	else
	{
	ft_printf("\nHERE\n");
		
	}
}

int			is_cat_heredoc(t_var *data)
{
	if (data->cat_here != 0)
	{
//		if (data->cat_here == 2)
//			add_dollar(data);
		if (data->in_redir == 1)
		{
			ft_printf("\nHERE\n");
			test_fd_heredoc(data, 1);
			return (1);
		}
		ft_putstr(data->here_stock);
		data->cat_here = 0;
		ft_strdel(&data->here_stock);
		free_tab(data->argv);
		ft_putchar('\n');
		if (data->in_redir == 1)
			test_fd_heredoc(data, 2);
		return (1);
	}
	return (0);
}

int			check_cmd(t_var *data)
{
	char	**split;

	split = ft_split(data->cmds[data->cmd_index], ' ');
	if (split[0][0] == '<' && split[0][1] == '<')
	{
		free_tab(split);
		return (0);
	}
	else
	{
		if (!ft_strcmp(split[0], "cat") && ft_strcmp(split[1], "-e"))
			data->cat_here = 1;
		else if (!ft_strcmp(split[0], "cat") && !ft_strcmp(split[1], "-e"))
			data->cat_here = 2;
		else
			data->cat_here = 0;
		free_tab(split);
		return (1);
	}
}

int			init_heredoc(t_var *data, t_redirection_cmd *rcmd)
{
	ft_putchar('\n');
	data->herend = ft_strdup(rm_char(rcmd->file, ' '));
	heredoc_prompt(data);
	if (!check_cmd(data))
	{
		free(rcmd->file);
		free(rcmd->cmd);
		free(rcmd);
		return (0);
	}
	return (1);
}

int			is_aggreg(char *file)
{
	if (!strcmp(file, "&0") || !strcmp(file, "&1") || !ft_strcmp(file, "&2"))
		return (1);
	return (0);
}
