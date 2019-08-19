/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:14:06 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:38:47 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void *mem;

	mem = malloc(size);
	if (!(mem))
		return (NULL);
	else
		return (ft_memset(mem, 0, size));
}
