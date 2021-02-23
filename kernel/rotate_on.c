/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_on.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:58:38 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 18:03:17 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	rotate_obj2(t_list_obj *obj, t_matrix v_y, t_matrix v_x,
t_vec3f loc)
{
	t_obj	*cur_obj;

	cur_obj = obj->content;
	if (cur_obj->name == TR)
	{
		cur_obj->p1 = sub(cur_obj->p1, loc);
		cur_obj->p2 = sub(cur_obj->p2, loc);
		cur_obj->p3 = sub(cur_obj->p3, loc);
		cur_obj->p1 = vec_mul_m(vec_mul_m(cur_obj->p1, v_y), v_x);
		cur_obj->p2 = vec_mul_m(vec_mul_m(cur_obj->p2, v_y), v_x);
		cur_obj->p3 = vec_mul_m(vec_mul_m(cur_obj->p3, v_y), v_x);
		cur_obj->normal = normalize(cross(sub(cur_obj->p2, cur_obj->p1),
									sub(cur_obj->p3, cur_obj->p1)));
	}
}

static	void	rotate_obj1(t_list_obj *obj, t_matrix v_y, t_matrix v_x,
t_vec3f loc)
{
	t_obj	*cur_obj;

	cur_obj = obj->content;
	if (cur_obj->name == SP)
	{
		cur_obj->center = sub(cur_obj->center, loc);
		cur_obj->center = vec_mul_m(vec_mul_m(cur_obj->center, v_y), v_x);
	}
	else if (cur_obj->name == PL)
	{
		cur_obj->center = sub(cur_obj->center, loc);
		cur_obj->center = vec_mul_m(vec_mul_m(cur_obj->center, v_y), v_x);
		cur_obj->normal = vec_mul_m(vec_mul_m(cur_obj->normal, v_y), v_x);
	}
	else if (cur_obj->name == SQ || cur_obj->name == CY)
	{
		cur_obj->center = sub(cur_obj->center, loc);
		cur_obj->center = vec_mul_m(vec_mul_m(cur_obj->center, v_y), v_x);
		cur_obj->normal = vec_mul_m(vec_mul_m(cur_obj->normal, v_y),
		v_x);
	}
	rotate_obj2(obj, v_y, v_x, loc);
}

static	void	rotate_objects(t_scene **scene, double dg_y, double dg_x,
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
		rotate_obj1(ptr, v_y, v_x, loc);
		ptr = ptr->next;
	}
	while (l_ptr)
	{
		pt = l_ptr->content->point;
		pt = sub(pt, loc);
		pt = vec_mul_m(vec_mul_m(pt, v_y), v_x);
		l_ptr->content->point = pt;
		l_ptr = l_ptr->next;
	}
}

static	void	angles(t_vec3f *cur, double *teta, double *phi)
{
	double x;
	double y;
	double z;

	x = (*cur).x;
	y = (*cur).y;
	z = (*cur).z;
	if (!y && !x)
		*phi = 0;
	else if (!x && y && y > 0)
		*phi = -45;
	else if (!x && y && y < 0)
		*phi = 135;
	else if ((x && y && y < 0 && x < 0) || (x && y && y > 0 && x < 0))
		*phi = -(180 + *phi - 45);
	else if ((x && y && y > 0 && x > 0) || (x && y && y < 0 && x > 0))
		*phi = -(*phi - 45);
	else if (!y && x && x < 0)
		*phi = -135;
	else if (!y && x && x > 0)
		*phi = 45;
	if (!z)
		*teta = 0;
	if (z > 0)
		*teta = -(*teta);
}

void			rotation(t_scene **scene, int num, double *fov, size_t pos)
{
	t_scene				*ptr;
	t_vec3f				cur;
	static t_vec3f		loc;
	static double		arr[3];

	if (!((*scene)->cams.lst_cams))
		return ;
	if (!pos)
	{
		ptr = *scene;
		num = (num >= 0 ? num : (g_camnum + num % (g_camnum))) % g_camnum;
		while (num != ptr->cams.lst_cams->num)
			ptr->cams.lst_cams = ptr->cams.lst_cams->next;
		cur = ptr->cams.lst_cams->content->dir;
		loc = ptr->cams.lst_cams->content->point;
		*fov = ptr->cams.lst_cams->content->fov;
		arr[0] = 90 - (atan(sqrt(cur.x * cur.x + cur.y * cur.y) / fabs(cur.z)) *
		180 / M_PI);
		arr[1] = atan(cur.y / cur.x) * 180 / M_PI;
		angles(&cur, &arr[0], &arr[1]);
		rotate_objects(scene, arr[1] * M_PI / 180, arr[0] * M_PI / 180, loc);
	}
	else
		rotate_objects_back(scene, arr[1] * M_PI / 180, arr[0] * M_PI / 180,
		loc);
}
