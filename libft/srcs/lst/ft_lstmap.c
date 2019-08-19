/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 19:21:05 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:37:42 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *m;
	t_list *first;
	t_list *new;

	if (!(lst))
		return (NULL);
	m = f(lst);
	if ((new = ft_lstnew(m->content, m->content_size)) == NULL)
		return (NULL);
	first = new;
	lst = lst->next;
	while (lst)
	{
		m = f(lst);
		if ((new->next = ft_lstnew(m->content, m->content_size)) == NULL)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
