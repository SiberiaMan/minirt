/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:17:40 by dchani            #+#    #+#             */
/*   Updated: 2021/02/19 20:38:08 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	t_vec3f	get_col(t_matrix m)
{
	if (m.v3.x > 255)
		m.v3.x = 255;
	if (m.v3.y > 255)
		m.v3.y = 255;
	if (m.v3.z > 255)
		m.v3.z = 255;
	return (m.v3);
}

static	t_vec3f	get_rgb(t_scene *s, double dli, t_matrix m)
{
	t_vec3f		amb;
	t_list_l	*ptr;
	t_vec3f		col_l;

	col_l = (t_vec3f){0, 0, 0};
	if (s->amb.lst_amb)
		amb = mul(s->amb.lst_amb->content->color, s->amb.lst_amb->content->k);
	if (s->amb.lst_amb)
		m.v3 = mul(m.v3, dli + s->amb.lst_amb->content->k);
	else
		m.v3 = mul(m.v3, dli);
	if (s->amb.lst_amb)
		m.v3 = add(m.v3, amb);
	ptr = s->lights.lst_lts;
	while (ptr && dli)
	{
		if (ptr->content->inter)
			col_l = add(col_l, mul(ptr->content->color,
			ptr->content->intensity));
		ptr->content->inter = 0;
		ptr = ptr->next;
	}
	m.v3 = add(m.v3, col_l);
	return (get_col(m));
}

static	size_t	scene_intersect(t_vec3f orig, t_vec3f dir, t_scene *scene,
t_matrix *m)
{
	double		dist;
	t_list_obj	*ptr;
	t_obj		*obj;

	dist = 1e9;
	ptr = scene->objs.lst_objs;
	while (ptr)
	{
		obj = ptr->content;
		if (obj->name == SP && ray_to_sphere(orig, dir, obj, &dist))
			sp_matrix(obj, dir, add(orig, mul(dir, dist)), m);
		else if (obj->name == PL && ray_to_plane(orig, dir, obj, &dist))
			pl_matrix(obj, add(orig, mul(dir, dist)), m);
		else if (obj->name == TR && ray_to_tr(orig, dir, obj, &dist))
			tr_matrix(obj, add(orig, mul(dir, dist)), m);
		else if (obj->name == CY && ray_to_cyl(orig, dir, obj, &dist))
			cy_matrix(obj, dir, add(orig, mul(dir, dist)), m);
		else if (obj->name == SQ && ray_to_sq(orig, dir, obj, &dist))
			sq_matrix(obj, add(orig, mul(dir, dist)), m);
		ptr = ptr->next;
	}
	return (dist < 1000);
}

static	size_t	shadows(t_vec3f orig, t_vec3f dir, t_scene *scene,
double light_distance)
{
	t_matrix	m;

	if (scene_intersect(orig, dir, scene, &m)
	&& len(sub(m.v1, orig)) <= light_distance)
		return (0);
	return (1);
}

t_vec3f			cast_ray(t_vec3f orig, t_vec3f dir, t_scene *scene)
{
	t_matrix	m;
	t_vec3f		light_dir;
	double		light_dist;
	double		dli;
	t_list_l	*ptr;

	dli = 0;
	if (!scene_intersect(orig, dir, scene, &m))
		return ((t_vec3f){200, 165, 40});
	ptr = scene->lights.lst_lts;
	while (ptr)
	{
		light_dir = normalize(sub(ptr->content->point, m.v1));
		light_dist = len(sub(ptr->content->point, m.v1));
		if (shadows(add(m.v1, mul(m.v2, 1e-5)), light_dir, scene, light_dist))
		{
			dli += ptr->content->intensity * fmax(0.f, dot(light_dir, m.v2));
			ptr->content->inter = 1;
		}
		ptr = ptr->next;
	}
	return (get_rgb(scene, dli, m));
}
