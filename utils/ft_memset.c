/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:13:49 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 17:43:34 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buff, int c, size_t len)
{
	int i;

	i = 0;
	while (len--)
	{
		((unsigned char*)buff)[i] = (unsigned char)c;
		i++;
	}
	return (buff);
}
