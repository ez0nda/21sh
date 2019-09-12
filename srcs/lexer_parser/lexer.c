/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:41:54 by jebrocho          #+#    #+#             */
/*   Updated: 2019/09/10 12:36:12 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void		disp_mod(char *buff, char **lexer, t_stat *stat, int mod)
{
	if (mod == 1)
		while (ft_strchr(ENDI, buff[stat->index]) == NULL && buff[stat->index])
			lexer[stat->tab_lex][stat->in_lex++] = buff[stat->index++];
	if (mod == 2)
		while (ft_strchr(SEPAR, buff[stat->index]) == NULL && buff[stat->index])
			lexer[stat->tab_lex][stat->in_lex++] = buff[stat->index++];
	if (mod == 3)
		while (ft_strchr(ENDI, buff[stat->index]) == NULL)
			lexer[stat->tab_lex][stat->in_lex++] = buff[stat->index++];
}

void		algo_lexer(char *buff, char **lexer, t_stat *stat, int mod)
{
	if (mod == 0)
	{
		if (buff[stat->index] == '#')
		{
			while (buff[stat->index])
				lexer[stat->tab_lex][stat->in_lex++] = buff[stat->index++];
			lexer[stat->tab_lex][stat->in_lex] = '\0';
			stat->tab_lex++;
		}
		return ;
	}
	disp_mod(buff, lexer, stat, mod);
	if (mod == 4)
	{
		lexer[stat->tab_lex] = NULL;
		stat->tab_lex = 0;
		return ;
	}
	lexer[stat->tab_lex][stat->in_lex] = '\0';
	stat->in_lex = 0;
	stat->tab_lex++;
	stat->index--;
}

char		**malloc_lexer(int nb_words)
{
	int		cmd;
	char	**lexer;

	cmd = 0;
	if (!(lexer = (char**)malloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	while (nb_words-- > 0)
		if (!(lexer[cmd++] = (char*)malloc(sizeof(char) * 1000)))
			return (NULL);
	return (lexer);
}

void		condition_lexer(char *buff, char **lexer, t_stat *stat)
{
	if (ft_strchr(SEPAR, buff[stat->index]) == NULL
			&& ft_strchr(ENDI, buff[stat->index]) == NULL && stat->cmd == 0)
	{
//		write(1, "a\n", 2);
		stat->cmd = 1;
		algo_lexer(buff, lexer, stat, 1);
//		write(1, "a\n", 2);
	}
	else if (stat->cmd == 1 && ft_strchr(SEPAR, buff[stat->index]) == NULL
			&& ft_strchr(SEPAR, buff[stat->index + 1]) == NULL)
	{
//		write(1, "b\n", 2);
		algo_lexer(buff, lexer, stat, 2);
//		write(1, "b\n", 2);
	}
	else if (stat->cmd == 1 && ft_strchr(SEPAR, buff[stat->index]) != NULL)
	{
//		write(1, "c\n", 2);
		stat->cmd = 0;
		algo_lexer(buff, lexer, stat, 3);
//		write(1, "c\n", 2);
	}
}

char *new_spaces(char *buff, int i)
{
	int save;
	int j;
	char *tmp;
	int savethis;

	j = 0;
	i++;
	save = i;
	savethis = i;
//	ft_printf("\nc_spaces: %c\n", buff[i]);
	while (buff[i])
		i++;
	if (!(tmp = (char*)malloc(sizeof(char) * (i - save + 1))))
		return (NULL);
	while (save < i)
	{
		tmp[j] = buff[save];
		j++;
		save++;
	}
	tmp[j] = '\0';
	buff[savethis] = '\0';
	buff = ft_strjoin_free(buff, " ", 0);
	buff = ft_strjoin_free(buff, tmp, 2);
	return (buff);
}

char *space_this(char *buff)
{
	int i;

	i = -1;
	while (buff[++i])
	{
		if (buff[i + 1])
		{
			if (ft_strchr(SEPAR, buff[i]) == NULL)
				if (ft_strchr(SEPAR, buff[i + 1]) != NULL
			 			&& ft_strchr(ENDI, buff[i]) == NULL)
						buff = new_spaces(ft_strdup(buff), i);
			if (ft_strchr(SEPAR, buff[i]) != NULL)
				if (ft_strchr(ENDI, buff[i + 1]) == NULL
						&& ft_strchr(SEPAR, buff[i + 1]) == NULL
						&& ft_strchr("012", buff[i + 1]) == NULL)
						buff = new_spaces(ft_strdup(buff), i);
		}

	}
	return (buff);
}

char		**lexer(char *buff)
{
	char		**lexer;
	int			test;
	t_stat	stat;

	test = -1;
	stat.cmd = 0;
	stat.index = -1;
	stat.in_lex = 0;
	stat.tab_lex = 0;
//	write(1, "start\n", 6);
//	getchar();
//	write(1, "space\n", 6);
	buff = space_this(buff);
//	ft_printf("%s\n", buff);
//	getchar();
//	write(1, "malloc lex\n", 11);
	lexer = malloc_lexer(count_lex(buff));
//	getchar();
//	write(1, "algo\n", 5);
	while (buff[++stat.index])
	{
		if (stat.cmd == 0 && ft_strchr(SEPAR, buff[stat.index]) != NULL)
			stat.cmd = 1;
		algo_lexer(buff, lexer, &stat, 0);
		condition_lexer(buff, lexer, &stat);
	}
//	getchar();
//	write(1, "mod4A\n", 5);
	algo_lexer(buff, lexer, &stat, 4);
//	getchar();
//	write(1, "rmspace\n", 8);
	first_space(lexer);
	return (lexer);
}
