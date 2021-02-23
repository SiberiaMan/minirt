/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:14:50 by dchani            #+#    #+#             */
/*   Updated: 2021/02/15 19:14:51 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

size_t		color_check(t_vec3f *color)
{
	if (!(0 <= color->x && 0 <= color->y && 0 <= color->z
	&& color->x <= 255 && color->y <= 255 && color->z <= 255))
		return (0);
	return (1);
}

size_t		normal_check(t_vec3f *normal)
{
	if (!(0 <= fabs(normal->x) && 0 <= fabs(normal->y)
	&& 0 <= fabs(normal->z) && fabs(normal->x) <= 1
	&& fabs(normal->y) <= 1 && fabs(normal->z) <= 1))
		return (0);
	return (1);
}
