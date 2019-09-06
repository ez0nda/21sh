/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:15:39 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/05 12:16:39 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "core.h"

char			**ft_tabdup(char **tab);
int				ft_tablen(char **tab);
void			init_shell(t_var *data);
int				ft_putchar_v2(int c);

#endif
