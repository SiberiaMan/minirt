/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:30:31 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 20:30:32 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			len(t_vec3f v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3f			normalize(t_vec3f v)
{
	double l;

	l = len(v);
	return ((t_vec3f) {
		v.x / l,
		v.y / l,
		v.z / l
	});
}
