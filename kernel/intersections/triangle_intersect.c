/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:59:29 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 21:02:41 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static	size_t		tr_intersect2(t_obj *obj, t_vec3f point)
{
	t_vec3f		e1;
	t_vec3f		e2;
	t_vec3f		temp;

	e1 = normalize(sub(obj->p2, obj->p3));
	e2 = normalize(sub(obj->p1, obj->p3));
	temp = normalize(sub(point, obj->p3));
	if (!(dot(e1, e2) <= dot(e1, temp) && dot(e1, e2) <= dot(e2, temp)))
		return (0);
	return (1);
}

size_t				tr_intersect1(t_vec3f orig, t_vec3f dir, double *t0,
t_obj *obj)
{
	t_vec3f		e1;
	t_vec3f		e2;
	t_vec3f		temp;
	t_vec3f		l;
	t_vec3f		point;

	if (dot(dir, obj->normal) < 0)
		obj->normal = mul(obj->normal, -1);
	if (dot(obj->normal, dir) > 1e-10)
	{
		l = sub(obj->p1, orig);
		*t0 = dot(l, obj->normal) / dot(obj->normal, dir);
	}
	if (*t0 < 1e-10)
		return (0);
	point = add(orig, mul(dir, *t0));
	e1 = normalize(sub(obj->p2, obj->p1));
	e2 = normalize(sub(obj->p3, obj->p1));
	temp = normalize(sub(point, obj->p1));
	if (!(dot(e1, e2) <= dot(e1, temp) && dot(e1, e2) <= dot(e2, temp)))
		return (0);
	return (tr_intersect2(obj, point));
}
