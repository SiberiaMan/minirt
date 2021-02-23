/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_off.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:47:59 by dchani            #+#    #+#             */
/*   Updated: 2021/02/15 19:23:59 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	rotate_obj2(t_list_obj *obj, t_matrix v_y, t_matrix v_z,
t_vec3f loc)
{
	t_obj	*cur_obj;

	cur_obj = obj->content;
	if (cur_obj->name == TR)
	{
		cur_obj->p1 = vec_mul_m(vec_mul_m(cur_obj->p1, v_y),
		v_z);
		cur_obj->p2 = vec_mul_m(vec_mul_m(cur_obj->p2, v_y),
		v_z);
		cur_obj->p3 = vec_mul_m(vec_mul_m(cur_obj->p3, v_y),
		v_z);
		cur_obj->p1 = add(cur_obj->p1, loc);
		cur_obj->p2 = add(cur_obj->p2, loc);
		cur_obj->p3 = add(cur_obj->p3, loc);
		cur_obj->normal = normalize(cross(sub(cur_obj->p2, cur_obj->p1),
									sub(cur_obj->p3, cur_obj->p1)));
	}
}

static	void	rotate_obj1(t_list_obj *obj, t_matrix v_y, t_matrix v_z,
t_vec3f loc)
{
	t_obj	*cur_obj;

	cur_obj = obj->content;
	if (cur_obj->name == SP)
	{
		cur_obj->center = vec_mul_m(vec_mul_m(cur_obj->center, v_y), v_z);
		cur_obj->center = add(cur_obj->center, loc);
	}
	else if (cur_obj->name == PL)
	{
		cur_obj->center = vec_mul_m(vec_mul_m(cur_obj->center, v_y), v_z);
		cur_obj->normal = vec_mul_m(vec_mul_m(cur_obj->normal, v_y), v_z);
		cur_obj->center = add(cur_obj->center, loc);
	}
	else if (cur_obj->name == SQ || cur_obj->name == CY)
	{
		cur_obj->center = vec_mul_m(vec_mul_m(cur_obj->center, v_y), v_z);
		cur_obj->normal = vec_mul_m(vec_mul_m(cur_obj->normal, v_y), v_z);
		cur_obj->center = add(cur_obj->center, loc);
	}
	rotate_obj2(obj, v_y, v_z, loc);
}

void			rotate_objects_back(t_scene **scene, double dg_y, double dg_x,
t_vec3f loc)
{
	t_matrix	v_y;
	t_matrix	v_x;
	t_list_obj	*ptr;
	t_list_l	*l_ptr;
	t_vec3f		pt;

	v_y = matrix3_init((t_vec3f){cos(dg_y), 0, -sin(dg_y)}, (t_vec3f){0, 1, 0},
	(t_vec3f){sin(dg_y), 0, cos(dg_y)});
	v_x = matrix3_init((t_vec3f){1, 0, 0}, (t_vec3f){0, cos(dg_x), sin(dg_x)},
	(t_vec3f){0, -sin(dg_x), cos(dg_x)});
	ptr = (*scene)->objs.lst_objs;
	l_ptr = (*scene)->lights.lst_lts;
	while (ptr)
	{
		rotate_obj1(ptr, inv_mx3(v_x), inv_mx3(v_y), loc);
		ptr = ptr->next;
	}
	while (l_ptr)
	{
		pt = l_ptr->content->point;
		pt = vec_mul_m(vec_mul_m(pt, inv_mx3(v_x)), inv_mx3(v_y));
		pt = add(pt, loc);
		l_ptr->content->point = pt;
		l_ptr = l_ptr->next;
	}
}
