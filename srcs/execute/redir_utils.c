/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:59:19 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/06 09:50:23 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

char		*close_fd(char *file)
{
	free(file);
	file = ft_strdup("/dev/null");
	return (file);
}

int			is_cat_heredoc(t_var *data)
{
	if (data->cat_here)
	{
		data->cat_here = 0;
		ft_putstr(data->here_stock);
		ft_strdel(&data->here_stock);
		free_tab(data->argv);
		ft_putchar('\n');
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
		if (!ft_strcmp(split[0], "cat"))
			data->cat_here = 1;
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
