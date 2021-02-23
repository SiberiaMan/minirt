/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:34:22 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 20:51:28 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static	double		diskr(t_vec3f orig, t_vec3f dir, t_obj *obj)
{
	t_vec3f			l;
	double			a;
	double			b;
	double			c;
	double			d;

	l = sub(orig, obj->center);
	a = dot(dir, dir) - pow(dot(obj->normal, dir), 2);
	b = 2 * (dot(l, dir) - dot(obj->normal, l) * dot(obj->normal, dir));
	c = dot(l, l) - pow(dot(obj->normal, l), 2) - (obj->d / 2) * (obj->d /
			2);
	d = b * b - 4 * a * c;
	return (d);
}

static	double		get_a(t_vec3f dir, t_obj *obj)
{
	return (dot(dir, dir) - pow(dot(obj->normal, dir), 2));
}

static	double		get_b(t_vec3f orig, t_vec3f dir, t_obj *obj)
{
	t_vec3f		l;

	l = sub(orig, obj->center);
	return (2 * (dot(l, dir) - dot(obj->normal, l) * dot(obj->normal, dir)));
}

static size_t		cyl_intersect2(double *t0, t_vec3f orig, t_vec3f dir,
t_obj *obj)
{
	t_vec3f		ht;

	if (*t0 < 0)
		return (0);
	ht = add(orig, mul(dir, *t0));
	if (fabs(dot(obj->normal, sub(ht, obj->center))) > obj->side / 2)
		return (0);
	return (1);
}

size_t				cyl_intersect1(t_vec3f o, t_vec3f d, double *t0, t_obj *ob)
{
	double		t1;
	double		t2;

	if (diskr(o, d, ob) < 0)
		return (0);
	else if (diskr(o, d, ob) == 0)
		*t0 = get_b(o, d, ob) / (2 * get_a(d, ob)) * (-1);
	else
	{
		t1 = (-get_b(o, d, ob) + sqrt(diskr(o, d, ob))) / (2 * get_a(d, ob));
		t2 = (-get_b(o, d, ob) - sqrt(diskr(o, d, ob))) / (2 * get_a(d, ob));
		if (t1 < 0 && t2 < 0)
			return (0);
		*t0 = fmin(t1, t2);
		if (*t0 < 0)
			*t0 = fmax(t1, t2);
		if (fabs(dot(ob->normal, sub(add(o, mul(d, *t0)), ob->center))) >
		ob->side / 2)
		{
			*t0 = (*t0 == t1 ? t2 : t1);
			if (!(cyl_intersect2(t0, o, d, ob)))
				return (0);
		}
	}
	return (1);
}
