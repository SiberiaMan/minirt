/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:19:49 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:37:06 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		i;

	i = 0;
	ptr = (void*)malloc(size * count);
	if (!ptr)
		return (0);
	while (i < size * count)
	{
		((unsigned char*)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
