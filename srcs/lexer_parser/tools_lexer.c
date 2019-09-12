/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:42:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/09/02 15:31:42 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	last_word(char **lexer, int index)
{
	int		i;
	int		j;
	int		save;

	j = 0;
	i = ft_strlen(lexer[index]) - 1;
	while (ft_strchr(ENDI, lexer[index][i]) == NULL)
		i--;
	save = i;
	ft_bzero(lexer[index + 1], 1000);
	while (lexer[index][i])
		lexer[index + 1][j++] = lexer[index][i++];
	lexer[index + 1][j] = '\0';
	lexer[index][save] = '\0';
	save = index;
	if (ft_strcmp(lexer[index], "") == 0)
	{
		while (lexer[index + 1])
		{
			lexer[index] = lexer[index + 1];
			index++;
		}
		lexer[index] = NULL;
	}
}

void	ft_joinredir(char **lexer)
{
	int ind;

	ind = -1;
	while (lexer[++ind])
	{
		if (lexer[ind][0] == '>' || lexer[ind][0] == '<')
		{
			if (ind > 0)
			{
				if (ft_strchr("012",
					lexer[ind - 1][ft_strlen(lexer[ind - 1]) - 1]) != NULL)
				{
					lexer[ind - 1] = ft_strjoin_free(lexer[ind - 1], lexer[ind], 0);
					last_word(lexer, ind - 1);
				}
			}
		}
	}
}

void	first_space(char **lexer)
{
	int		index;
	int		in_lex;

	index = 0;
	in_lex = 0;
//	write(1, "a", 1);
//	getchar();
	ft_joinredir(lexer);
//	write(1, "b", 1);
//	getchar();
	while (lexer[index])
	{
		if (lexer[index][0] == ' ')
		{
			while (lexer[index][in_lex + 1])
			{
				lexer[index][in_lex] = lexer[index][in_lex + 1];
				in_lex++;
			}
			lexer[index][in_lex] = '\0';
			in_lex = 0;
		}
		index++;
	}
//	write(1, "c", 1);
//	getchar();
}
/*
int 	count_algo(int mod)
{

}*/

int		count_lex(char *buff)
{
	int i;
	int InWord;
	int nbWords;
	int cmd;
	int save;

	i = -1;
	InWord = 0;
	nbWords = 0;
	cmd = 0;
	save = 0;
	while (buff[++i])
	{
		if (buff[i] == '#')
			return (nbWords + 1);
		if (buff[i] == '\"')
			InWord++;
		if (ft_strchr(ENDI, buff[i]) == NULL && (InWord % 2) == 0 && cmd == 0)
		{
			if (ft_strchr(SEPAR, buff[i]) == NULL)
				cmd = 1;
			nbWords++;
			while (ft_strchr(ENDI, buff[i]) == NULL)
				i++;
			i--;
		}
		else if (cmd == 1 && ft_strchr(ENDI, buff[i]) == NULL)
		{
			if (buff[i] == '\"')
				InWord++;
			cmd = 0;
			if (ft_strchr(SEPAR, buff[i]) == NULL)
				nbWords++;
			while (ft_strchr(SEPAR, buff[i]) == NULL)
				i++;
			save = 0;
			i--;
		}
	}
	return (nbWords);
}
