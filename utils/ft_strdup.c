/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:32:30 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:37:48 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_strlen4(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char				*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;
	char	*bptr;

	len = ft_strlen4(s1);
	ptr = (char*)malloc(len + 1);
	bptr = ptr;
	if (!ptr)
		return (0);
	while (*s1)
	{
		*ptr = *s1;
		s1++;
		ptr++;
	}
	*ptr = *s1;
	return (bptr);
}
