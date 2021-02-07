/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:39:28 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:55:19 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t			ft_strlen2(const char *restrict s)
{
	size_t len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

size_t					ft_strlcpy(char *restrict dst,
						const char *restrict src, size_t dstsize)
{
	size_t		len_src;
	size_t		return_value;

	if (!dst && !src)
		return (0);
	len_src = ft_strlen2(src);
	return_value = len_src;
	if (len_src + 1 < dstsize)
	{
		while (len_src--)
			*dst++ = *src++;
		*dst = '\0';
	}
	else if (dstsize != 0)
	{
		dstsize--;
		while (dstsize--)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (return_value);
}
