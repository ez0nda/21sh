/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:31:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/09/02 14:06:52 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEPAR "<>|;&"
#define ENDI   "\n\t \0"
#define NMETA "\"\'"

typedef struct  s_stat
{
  int   index;
  int   in_lex;
  int   tab_lex;
  int   res;
  int   cmd;
  char  **lexer;
}               t_stat;

char  **lexer(char *buff);
void first_space(char **lexer);
void last_word(char **lexer, int index);
void ft_joinredir(char **lexer);
int  count_lex(char *buff);

#endif
