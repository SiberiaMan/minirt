/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:30:07 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 20:41:56 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t	square_intersect(t_vec3f orig, t_vec3f dir, double *t0, t_obj *obj)
{
	double		denom;
	t_vec3f		l;
	t_vec3f		d;
	t_vec3f		i;
	t_vec3f		j;

	if (dot(dir, obj->normal) < 0)
		obj->normal = mul(obj->normal, -1);
	denom = dot(obj->normal, dir);
	if (denom > 1e-6)
	{
		l = sub(obj->center, orig);
		*t0 = dot(l, obj->normal) / denom;
	}
	j = normalize(cross(obj->normal, (t_vec3f){0, 1, 0}));
	if (-0.00001 <= j.x && j.x <= 0.00001 && -0.00001 <= j.y
	&& j.y <= 0.00001 && -0.00001 <= j.z && j.z <= 0.00001)
		j = normalize(cross(obj->normal, (t_vec3f){1, 0, 0}));
	i = normalize(cross(j, obj->normal));
	d = sub(add(orig, mul(dir, *t0)), obj->center);
	if (fabs(dot(d, i)) <= obj->side / 2 && fabs(dot(d, j)) <= obj->side / 2
	&& *t0 > 0)
		return (1);
	return (0);
}
