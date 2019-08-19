/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:00:39 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:37:54 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *m;

	m = malloc(sizeof(t_list));
	if (m == NULL)
		return (NULL);
	if (content == NULL)
	{
		m->content = NULL;
		m->content_size = 0;
	}
	else
	{
		if (!(m->content = malloc(sizeof(m->content_size))))
			return (NULL);
		ft_memcpy(m->content, content, content_size);
		m->content_size = content_size;
	}
	m->next = NULL;
	return (m);
}
