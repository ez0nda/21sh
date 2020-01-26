/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:21:46 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/03 14:14:19 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int		ft_is_in(char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_lstadd_back(t_list **alst, t_list *nw)
{
	while (*alst)
		alst = &(*alst)->next;
	*alst = nw;
	while (nw)
		nw = nw->next;
}

int		is_pipe(char c)
{
	if (c == ';' || c == '|')
		return (1);
	return (0);
}

int		is_whitespaces(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\n' || c == ';')
		return (1);
	return (0);
}

int		ft_lstcount(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}
