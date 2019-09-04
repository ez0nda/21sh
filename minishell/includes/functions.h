/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:35:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:56:52 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "struct.h"

char	**ft_split(char *str, char c);
char	**ft_split_whitespace(char *str);
void	print_error(char *buf);
char	*get_env(char *str);
char	*first_whitespace(char *buf);
void	rm_one(char *buf, int k);
char	*rm_whitespace(char *buf, t_env *v);
char	**parse_command(char *buf);
char	**parse_line(char *buf);
int		builtin(char *buf, t_env *v);
int		line_of_env(char *str);
void	parse_arg(char *str, char c, t_env *v);
void	change_env(char *str, char *selec, t_env *v);
int		ft_cd(char **line, t_env *v);
void	add_last(char *str, t_env *v);
void	rm_last(t_env *v);
char	**ft_echo(char *line);
char	**ft_split_whitespace_exp(char *str);
int		detect_echo(char **line);
int		ft_setenv(char **line, t_env *v);
int		p_env(void);
int		ft_unsetenv(char **line);
void	ctrl(int signal);
char	*get_pwd(void);
char	*parse_error(char *s, t_env *v);
int		error_env(void);
int		ft_reset(t_env *v);
char	*get_env_val(char *str);
void	error_path(int mod, char *line);
int		error_cd(char *str, int mod);
char	*ft_strjoin_free(char *s1, char *s2, int mod);
int		free_tab(char **t);
char	*add_error(char *s, char *n);
void	rm_error(char *s);
void	new_env(char *l, t_env *v);
char	*expansions(char *buf, t_env *v);

#endif
