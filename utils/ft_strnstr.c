/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:43:40 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:38:45 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_strlen3(const char *s)
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

char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len)
{
	size_t			cnt;
	size_t			i;
	size_t			j;
	size_t			k;

	i = 0;
	if (ft_strlen3(needle) == 0)
		return ((char*)haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			k = i;
			cnt = 0;
			j = 0;
			while (haystack[k] && needle[j] && haystack[k++] == needle[j++]
					&& i + j <= len)
				cnt++;
			if (cnt == ft_strlen3(needle))
				return (&((char*)haystack)[i]);
		}
		i++;
	}
	return (0);
}
