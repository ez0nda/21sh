/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:34:02 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/23 15:50:19 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_cmd		*parse_redir(t_cmd *cmd, char **p, char *end)
{
	int		tok;
	char	*q;
	char	*eq;
	char	*f;

	while (strings_scan_whitespaces(p, end, "12<>"))
	{
		if ((**p == '1' || **p == '2') && (*p)[1] != '>' && (*p)[1] != '<')
			break ;
		tok = tokenizer(p, end, 0, 0);
		tokenizer(p, end, &q, &eq);
		if ((f = ft_strndup(q, eq - q + 1)) && tok == '<')
			cmd = parse_redir_cmd(cmd, f, M_READ, 0);
		if (tok == '>')
			cmd = parse_redir_cmd(cmd, f, M_WRITE_TRUNC, 1);
		if (tok == '+')
			cmd = parse_redir_cmd(cmd, f, M_WRITE_APPEND, 1);
		if (tok == '=')
			cmd = parse_redir_cmd(cmd, f, M_READ_APPEND, 0);
		if (tok == '*')
			cmd = parse_redir_cmd(cmd, f, M_WRITE_TRUNC, 2);
		if (tok == '/')
			cmd = parse_redir_cmd(cmd, f, M_WRITE_APPEND, 2);
	}
	return (cmd);
}

t_cmd		*parse_basic(char **p_input, char *end, int *res)
{
	char			*new_cmd[2];
	int				tok;
	t_exec_cmd		*cmd;
	t_cmd			*ret;
	char			*tmp;

	ret = parse_basic_cmd();
	cmd = (t_exec_cmd *)ret;
	cmd->argv = NULL;
	ret = parse_redir(ret, p_input, end);
	while (*p_input < end)
	{
		if ((tok = tokenizer(p_input, end, &new_cmd[0], &new_cmd[1])) == 0)
			break ;
		if (tok != 'a' && (*res = 0))
			return (NULL);
		tmp = ft_strndup(new_cmd[0], new_cmd[1] - new_cmd[0]);
		ft_lstadd_back(&cmd->argv, ft_lstnew(tmp, new_cmd[1] - new_cmd[0] + 1));
//		free(tmp);
		ret = parse_redir(ret, p_input, end);
	}
	return (ret);
}

t_cmd		*parse_pipe(char **p_input, char *end, int *res)
{
	t_cmd	*cmd;
	char	*new_cmd;
	char	*new_cmd_end;

	if (strings_scan_pipes(
		p_input, end, &new_cmd, &new_cmd_end))
	{
		cmd = parse_basic(&new_cmd, new_cmd_end, res);
		(*p_input)++;
		cmd = parse_pipe_cmd(
			cmd, parse_pipe(p_input, end, res));
	}
	else
		cmd = parse_basic(&new_cmd, new_cmd_end, res);
	return (cmd);
}

t_cmd		*shell_parser(char *input)
{
	char		*end;
	t_cmd		*cmd;
	int			res;

	res = 1;
	end = input + ft_strlen(input);
	cmd = parse_pipe(&input, end, &res);
	return (cmd);
}
