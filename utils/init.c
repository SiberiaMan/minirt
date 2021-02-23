/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:49:34 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 17:49:36 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		init(t_objects *o, t_cameras *c, t_ambient *a, t_lights *l)
{
	o->valid = 1;
	o->lone_cy = 0;
	o->lone_pl = 0;
	o->lone_sp = 0;
	o->lone_sq = 0;
	o->lone_tr = 0;
	o->nolone_cy = 0;
	o->nolone_pl = 0;
	o->nolone_sp = 0;
	o->nolone_sq = 0;
	o->nolone_tr = 0;
	o->lst_objs = 0;
	c->valid = 1;
	c->lone_camera = 0;
	c->nolone_camera = 0;
	c->lst_cams = 0;
	a->valid = 1;
	a->lst_amb = 0;
	a->lone_ambient = 0;
	a->nolone_ambient = 0;
	l->valid = 1;
	l->lone_light = 0;
	l->nolone_light = 0;
	l->lst_lts = 0;
}

t_scene		*init_scene(t_scene *scene)
{
	t_objects	objects;
	t_cameras	cameras;
	t_ambient	ambient;
	t_lights	lights;

	init(&objects, &cameras, &ambient, &lights);
	*scene = (t_scene){
			.objs = objects,
			.lights = lights,
			.cams = cameras,
			.amb = ambient,
			.valid = 1,
			.is_resolution = 0,
			.sv = 0
	};
	return (scene);
}
