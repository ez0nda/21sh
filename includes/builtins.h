/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:42:07 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/10 14:25:34 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core.h"
# include <dirent.h>

int		env_builtin(char **environ);
int		setenv_builtin(t_var *data, char **cmd);
int		unsetenv_builtin(t_var *data, char **cmd);
char	**ft_echo(char *str);
char  *get_env(char **environ, char *selec);

int   cd_builtin(t_var *data, char **cmd);
void  form_path(char *str, char c);
char	*error_cd(char *str, int mod);
char  *parse_error(char *s, t_var *data);
void	rm_error(char *s);


#endif
