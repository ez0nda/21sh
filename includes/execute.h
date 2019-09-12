/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:57:21 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/10 14:05:48 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "core.h"

char	*init_path(char *str, char *cmd);
void	error_msg(char **bin_path, char *path);
int		free_tab(char **tab);
char	*get_var(char *str, char **env);
char	*get_dollar_var(char *cmd, t_var *data);
void	exec_cmd(char **bin_path, char **lexer, t_var *data);
void	init_exec(t_var *data);

#endif
