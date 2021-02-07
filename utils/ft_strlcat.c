/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:57:35 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 22:11:36 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t			ft_strlen1(const char *restrict s)
{
	size_t len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

static	size_t			ft_strnlen1(char *restrict s, size_t length)
{
	size_t len;

	len = 0;
	while (length-- && *s)
	{
		len++;
		s++;
	}
	return (len);
}

size_t					ft_strlcat(char *restrict dst,
						const char *restrict src, size_t dstsize)
{
	size_t		len_src;
	size_t		len_dest;
	size_t		len_remain;
	char		*cur;

	len_src = ft_strlen1(src);
	len_dest = ft_strnlen1(dst, dstsize);
	if (len_dest != dstsize && dstsize)
	{
		len_remain = dstsize - len_dest - 1;
		if (len_remain > len_src)
			len_remain = len_src;
		cur = dst + len_dest;
		while (len_remain--)
			*cur++ = *src++;
		*cur = '\0';
	}
	return (len_dest + len_src);
}
