/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:27:37 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:40:19 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t				len;
	unsigned int		i;
	char				*ptr;
	char				*bptr;

	i = 0;
	len = ft_strlen(s);
	ptr = (char*)malloc(len + 1);
	if (!ptr)
		return (0);
	bptr = ptr;
	while (i < len)
	{
		*ptr = f(i, s[i]);
		i++;
		ptr++;
	}
	*ptr = '\0';
	return (bptr);
}
