/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:33:36 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/05 11:08:15 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static int	tokenizer_redirection(char **s, int ret)
{
	(*s)++;
	if (**s == '>')
	{
		(*s)++;
		return ('+');
	}
	if (**s == '<')
	{
		(*s)++;
		return ('=');
	}
	return (ret);
}

static int	tokenizer_aggregators(char **s, int ret)
{
	if (*(*s + 1) == '>')
	{
		if (*(*s + 2) == '>')
		{
			ret = (**s == '1') ? '+' : '/';
			*s += 3;
		}
		else
		{
			ret = (**s == '1') ? '>' : '*';
			*s += 2;
		}
	}
	else
	{
		while (**s == '1' || **s == '2')
			*s += 1;
	}
	return (ret);
}

static int	tokenizer_string(char **s, char *end)
{
	while (*s < end && !ft_strchr(" \t\r\n\v", **s) &&
		!ft_strchr("<|>", **s))
		(*s)++;
	return ('a');
}

char		*skip_whitespaces(char *s, char *end)
{
	while (s < end && ft_strchr(" \t\r\n\v", *s))
		s++;
	return (s);
}

int			tokenizer(
	char **p_input, char *end, char **new_cmd, char **new_cmd_end)
{
	char	*s;
	int		ret;

	s = *p_input;
	s = skip_whitespaces(s, end);
	if (new_cmd)
		*new_cmd = s;
	ret = *s;
	if (*s && (ft_is_in("|();&", *s)))
	{
		s++;
		s = (*s && ft_is_in("12-", *s)) ? s + 1 : s;
	}
	else if (*s && ft_is_in("><", *s))
		ret = tokenizer_redirection(&s, ret);
	else if (*s && ft_is_in("12", *s))
		ret = tokenizer_aggregators(&s, ret);
	else if (*s)
		ret = tokenizer_string(&s, end);
	if (new_cmd_end)
		*new_cmd_end = s;
	s = skip_whitespaces(s, end);
	*p_input = s;
	return (ret);
}
