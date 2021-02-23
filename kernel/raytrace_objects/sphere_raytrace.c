/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_raytrace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:14:33 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 22:34:55 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t		ray_to_sphere(t_vec3f orig, t_vec3f dir, t_obj *obj,
double *dist_i)
{
	double	new_dist;

	if (sphere_intersect(orig, dir, &new_dist, obj) && new_dist < *dist_i)
	{
		*dist_i = new_dist;
		return (1);
	}
	return (0);
}

void		sp_matrix(t_obj *obj, t_vec3f dir, t_vec3f point, t_matrix *m)
{
	m->v1 = point;
	m->v2 = normalize(sub(m->v1, obj->center));
	if (dot(m->v2, dir) > 0)
		m->v2 = mul(m->v2, -1);
	m->v3 = obj->color;
}
