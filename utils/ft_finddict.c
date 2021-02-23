/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finddict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:56:13 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 12:56:15 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

size_t		ft_finddict(char const *dict, char const *buf)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(buf);
	while (i < len)
	{
		if (!(ft_strchr(dict, buf[i])))
			return (0);
		i++;
	}
	return (1);
}
