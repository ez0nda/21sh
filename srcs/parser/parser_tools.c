/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:21:46 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/22 12:42:30 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	strings_scan_whitespaces(
	char **p_input, char *end, char *search)
{
	char *tmp;

	tmp = *p_input;
	while (tmp < end && ft_strchr(WHITESPACES, *tmp))
		tmp++;
	*p_input = tmp;
	return (*tmp && ft_strchr(search, *tmp));
}

int	strings_scan_pipes(char **p_input, char *end,
	char **new_cmd, char **new_cmd_end)
{
	char *tmp;

	tmp = *p_input;
	while (tmp < end && ft_strchr(WHITESPACES, *tmp))
		tmp++;
	*new_cmd = tmp;
	while (tmp < end && !ft_strchr("|", *tmp))
		tmp++;
	*new_cmd_end = tmp;
	*p_input = tmp;
//	ft_printf("\np_input: {%s}\n", *p_input);
	return (tmp != end);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char *s2;
	size_t i;

	i = 0;
	if (!(s2 = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

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
	{
//		ft_printf(" -- cur : %s\n", nw->content);
		nw = nw->next;
	}
}

int		is_whitespaces(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
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
