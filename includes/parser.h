/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:01:24 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 12:59:51 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core.h"

enum					e_cmd_type
{
	BASIC,
	REDIR,
	PIPE,
	ERRROR
};

typedef enum e_cmd_type	t_cmd_type;

typedef	struct			s_cmd
{
	t_cmd_type			type;
}						t_cmd;

typedef struct			s_exec_cmd
{
	t_cmd_type			type;
	t_list				*argv;
}						t_exec_cmd;

typedef	struct			s_redirection_cmd
{
	t_cmd_type			type;
	t_cmd				*cmd;
	char				*file;
	int					mode;
	int					fd;
}						t_redirection_cmd;

typedef	struct			s_pipe_cmd
{
	t_cmd_type			type;
	t_cmd				*left;
	t_cmd				*right;
}						t_pipe_cmd;

int						tokenizer(
		char **p_input, char *end, char **new_cmd, char **new_cmd_end);
t_cmd					*shell_parser(char *input);
t_cmd					*parse_basic_cmd(void);
t_cmd					*parse_redir_cmd(
		t_cmd *subcmd, char *file, int mode, int fd);
t_cmd					*parse_pipe_cmd(t_cmd *left, t_cmd *right);
int						strings_scan_pipes(
		char **p_input, char *end, char **new_cmd, char **new_cmd_end);
int						strings_scan_whitespaces(
		char **p_input, char *end, char *search);
void					ft_lstadd_back(t_list **alst, t_list *nw);
int						ft_is_in(char *str, char c);
char					*ft_strndup(const char *s1, size_t n);
int						is_whitespaces(char c);
int						is_pipe(char c);
int						ft_lstcount(t_list *list);

int						check_quotes(t_var *data);
void					read_quotes(t_var *data, int i);
void					realloc_quotes(
		t_var *data, char *start, char *end, int last_pos);
void					quotes_loop(t_var *data);
void					dquotes_loop(t_var *data);
int						get_close_quotes(t_var *data, int index);
int						get_close_dquotes(t_var *data, int index);
void					parse_multi_quotes(t_var *data, int index, int mod);
void					parse_multi_dquotes(t_var *data, int index, int mod);
void					check_backslash(t_var *data);

int 					check_dquotes_end(t_var *data);
int	 					check_quotes_end(t_var *data);
void 					rm_dquotes(char *str, char c);

void 					add_exp(t_var *data);
void 					join_exp(t_var *data, char *stock, char *selec);
void  				apply_exp(t_var *data, char *selec, int j, int i);
char 					*get_exp(char *str, int index);


#endif
