/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_raytrace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:44:25 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 22:44:26 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t		ray_to_plane(t_vec3f orig, t_vec3f dir, t_obj *obj, double *dist_i)
{
	double	new_dist;

	if (plane_intersect(orig, dir, &new_dist, obj) && new_dist < *dist_i)
	{
		*dist_i = new_dist;
		return (1);
	}
	return (0);
}

void		pl_matrix(t_obj *obj, t_vec3f point, t_matrix *m)
{
	m->v1 = point;
	m->v2 = mul(obj->normal, -1);
	m->v3 = obj->color;
}
