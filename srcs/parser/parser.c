/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:34:02 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/24 15:22:25 by ezonda           ###   ########.fr       */
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
		{
		//	ft_printf("\nBREAK, **p:%c, (*p)[1]:%c\n", **p, (*p)[1]);
			break ;
		}
		tok = tokenizer(p, end, 0, 0);
		tokenizer(p, end, &q, &eq);
		if ((f = ft_strndup(q, eq - q + 1)) && tok == '<')
			cmd = parse_redir_cmd(cmd, f, M_READ, 0);
		if (tok == '>')
		{
//			ft_printf("\nparse_redir :\nfile : %s\n", f);
			cmd = parse_redir_cmd(cmd, f, M_WRITE_TRUNC, 1);
		}
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
	char			*new_cmd;
	char			*new_cmd_end;
	int				tok;
	t_exec_cmd		*cmd;
	t_cmd			*ret;

	ret = parse_basic_cmd();
	cmd = (t_exec_cmd *)ret;
	cmd->argv = NULL;
	ret = parse_redir(ret, p_input, end);
	while (*p_input < end)
	{
//		ft_printf("\np_input : %d -- end : %d -- diff : %d\n", *p_input, end, 
//				end - *p_input);
		if ((tok = tokenizer(p_input, end, &new_cmd, &new_cmd_end)) == 0)
		{
			ft_printf("\ntokenizer == 0\n");
			break ;
		}
//		ft_printf("\ntokenizer = %d\n", tok);
//		ft_printf("\nhere3\n");
//		getchar();
//		if (tok == 49 || tok == 50)
//			return (NULL) ;
		if (tok != 'a' && (*res = 0))
			return (NULL);
		ft_lstadd_back(&cmd->argv, ft_lstnew(
			ft_strndup(new_cmd, new_cmd_end - new_cmd),
			new_cmd_end - new_cmd + 1));
		ret = parse_redir(ret, p_input, end);
//		ft_printf("\np_input : %d -- end : %d -- diff : %d\n", *p_input, end, 
//				end - *p_input);
	}
//	ft_printf("\nHERE\n");
//	getchar();
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
//		ft_printf("\np_input: {%s}\n", *p_input);
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
/*	if (input != end || res == 0)
	{
		ft_putendl_fd("Syntax error", 2);
		return (NULL);
	}
	else*/
		return (cmd);
}
