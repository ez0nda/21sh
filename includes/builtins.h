/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:42:07 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 09:28:11 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core.h"

int		env_builtin(char **environ);
int		setenv_builtin(t_var *data, char **cmd);
int		unsetenv_builtin(t_var *data, char **cmd);
char	*get_env(char **environ, char *selec);

int		cd_builtin(t_var *data, char **cmd);
void	form_path(char *str, char c);
char	*error_cd(char *str, int mod);
char	*parse_error(char *s, t_var *data);
void	rm_error(char *s);
void	old_pwd(char *old, t_var *data);
void	new_env(t_var *data, char *newp);

int		echo_builtin(t_var *data, char **cmd);

#endif
