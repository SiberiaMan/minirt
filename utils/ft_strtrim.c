/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:02:46 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:39:14 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ft_find(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	char		*ptr;
	char		*bptr;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_find(s1[i], set))
		i++;
	while (j >= i && j >= 0 && ft_find(s1[j], set))
		j--;
	ptr = (char*)malloc(j - i + 2);
	if (!ptr)
		return (0);
	bptr = ptr;
	while (s1[i] && i <= j)
	{
		*ptr = s1[i];
		i++;
		ptr++;
	}
	*ptr = '\0';
	return (bptr);
}
