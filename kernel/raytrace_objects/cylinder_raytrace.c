/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_raytrace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:54:16 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 22:54:17 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t		ray_to_cyl(t_vec3f orig, t_vec3f dir, t_obj *obj, double *dist_i)
{
	double	new_dist;

	if (cyl_intersect1(orig, dir, &new_dist, obj) && new_dist < *dist_i)
	{
		*dist_i = new_dist;
		return (1);
	}
	return (0);
}

void		cy_matrix(t_obj *obj, t_vec3f dir, t_vec3f point, t_matrix *m)
{
	t_vec3f		l;
	t_vec3f		temp;

	l = sub(point, obj->center);
	temp = cross(obj->normal, mul(l, -1));
	m->v1 = point;
	m->v2 = normalize(cross(obj->normal, temp));
	if (dot(m->v2, dir) > 0)
		m->v2 = mul(m->v2, -1);
	m->v3 = obj->color;
}
