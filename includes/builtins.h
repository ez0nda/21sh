/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:42:07 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/11 11:26:17 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core.h"

int		env_builtin(char **environ);
int		setenv_builtin(t_var *data, char **cmd);
int		unsetenv_builtin(t_var *data, char **cmd);
char	**ft_echo(char *str);

#endif
