/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:26:58 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 19:26:59 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t		plane_intersect(t_vec3f orig, t_vec3f dir, double *t0, t_obj *obj)
{
	double		denom;
	t_vec3f		l;

	if (dot(dir, obj->normal) < 0)
		obj->normal = mul(obj->normal, -1);
	denom = dot(obj->normal, dir);
	if (denom > 1e-6)
	{
		l = sub(obj->center, orig);
		*t0 = dot(l, obj->normal) / denom;
		return (*t0 >= 0);
	}
	return (0);
}
