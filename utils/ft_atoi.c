/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:54:02 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:29:18 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			is_whitespaces(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' || c == ' '
	|| c == '\v' || c == '\t')
		return (1);
	return (0);
}

int					ft_atoi(const char *str)
{
	int		res;
	int		fl;

	res = 0;
	fl = 1;
	while (*str && is_whitespaces(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			fl = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * fl);
}
