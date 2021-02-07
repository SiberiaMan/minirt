/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:40:36 by dchani            #+#    #+#             */
/*   Updated: 2020/11/03 14:01:54 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*bptr;

	if (start < (unsigned int)ft_strlen(s))
	{
		ptr = (char*)malloc(len + 1);
		if (!ptr)
			return (0);
		bptr = ptr;
		s = s + start;
		while (*s && len--)
		{
			*ptr = *s;
			ptr++;
			s++;
		}
		*ptr = '\0';
		return (bptr);
	}
	ptr = (char*)malloc(1);
	*ptr = '\0';
	return (ptr);
}
