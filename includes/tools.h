/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:38:42 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/04 13:40:58 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "core.h"

int		ft_putchar_v2(int c);
void	init_shell(t_var *data);
int		ft_tablen(char **tab);
char	**ft_tabdup(char **tab);

#endif
