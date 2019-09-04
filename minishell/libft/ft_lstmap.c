/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:06:29 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/14 17:43:49 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*tmp;
	t_list		*nlist;
	t_list		*first;

	if (!lst)
		return (NULL);
	tmp = f(lst);
	if ((nlist = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
		return (NULL);
	first = nlist;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		if ((nlist->next = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
			return (NULL);
		nlist = nlist->next;
		lst = lst->next;
	}
	return (first);
}
