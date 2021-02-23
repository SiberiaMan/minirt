/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:54:02 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 14:04:41 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	int					is_whitespaces(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' || c == ' '
	|| c == '\v' || c == '\t')
		return (1);
	return (0);
}

static	double				floating_num(double res, const char *str)
{
	double		dec;
	double		hund;

	dec = 0;
	hund = 0;
	dec = *(str++) - '0';
	if (*str && ft_strchr("0123456789", *(str)))
		hund = *str - '0';
	res += (0.1 * dec + 0.01 * hund);
	return (res);
}

double						ft_atof(const char *str)
{
	double		res;
	int			fl;

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
	if (*(str++) == '.' && ft_strchr("0123456789", *(str)))
		res = floating_num(res, str);
	return (res * fl);
}
