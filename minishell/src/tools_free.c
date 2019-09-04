/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:28:09 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/07 12:49:19 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_join(char *s1, char *s2, int mod)
{
	if (mod == 0 || mod == 2)
		free(s1);
	if (mod == 1 || mod == 2)
		free(s2);
}

char	*ft_strjoin_free(char *s1, char *s2, int mod)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	free_join(s1, s2, mod);
	return (str);
}

int		free_tab(char **t)
{
	int i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
	return (1);
}
