/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:00:52 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 17:43:04 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned const char		*pref;
	unsigned char			*suf;
	int						i;

	i = 0;
	if (!dst && !src)
		return (0);
	pref = (unsigned const char*)src;
	suf = (unsigned char*)dst;
	if (pref > suf)
		while (len--)
			*suf++ = *pref++;
	else
	{
		pref = pref + len - 1;
		suf = suf + len - 1;
		while (len--)
			*suf-- = *pref--;
	}
	return (dst);
}
