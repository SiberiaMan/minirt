/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:20:46 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 18:20:47 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t		sphere_intersect(t_vec3f orig, t_vec3f dir, double *t0, t_obj *obj)
{
	t_vec3f		l;
	double		tca;
	double		d2;
	double		thc;
	double		t1;

	l = sub(obj->center, orig);
	tca = dot(l, dir);
	d2 = dot(l, l) - tca * tca;
	if (d2 > (obj->d / 2) * (obj->d / 2))
		return (0);
	thc = sqrt(obj->d / 2 * obj->d / 2 - d2);
	*t0 = tca - thc;
	t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return (0);
	g_intersect++;
	return (1);
}
