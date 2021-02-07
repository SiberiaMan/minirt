/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:05:06 by dchani            #+#    #+#             */
/*   Updated: 2021/02/07 16:05:08 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include "utils/libft.h"
# include "mlx/mlx.h"

# define ABS(x) (x > 0 ? x : x * (-1))
# define MIN(a, b) (a > b ? b : a)
# define MAX(a, b) (a > b ? a : b)

typedef enum 			e_names
{
	SP = 1, PL = 2, SQ = 3, CY = 4, TR = 5
}						t_names;

typedef struct 			e_Vec3f
{
	double 		x;
	double 		y;
	double 		z;
}						t_Vec3f;

typedef struct 			s_lt
{
	t_Vec3f		point;
	t_Vec3f		dir;
	size_t 		valid;
}						t_lt;

typedef struct 			s_amb
{
	double 		k;
	t_Vec3f 	color;
	size_t 		valid;
}						t_amb;

typedef struct 			s_cam
{
	t_Vec3f		point;
	t_Vec3f		dir;
	double 		fov;
	size_t 		valid;
}						t_cam;

typedef struct			s_obj
{
	t_names		name;
	size_t 		number;
	t_Vec3f 	center;
	t_Vec3f 	N;
	double 		r;
	double 		d;
	double		side;
	t_Vec3f 	p1;
	t_Vec3f 	p2;
	t_Vec3f 	p3;
	t_Vec3f 	material;
	size_t 		lone_sp;
	size_t 		lone_pl;
	size_t 		lone_sq;
	size_t 		lone_cy;
	size_t 		lone_tr;
	size_t 		valid;
}						t_obj;

typedef struct 			s_objects
{
	t_list		*lst_objs;
	size_t 		valid;
}						t_objects;

typedef struct 			s_lights
{
	t_list		*lst_lts;
	size_t 		valid;
}						t_lights;

typedef struct 			s_cameras
{
	t_list		*lst_cams;
	size_t 		valid;
}						t_cameras;

typedef struct 			s_ambient
{
	t_list		*lst_amb;
	size_t		valid;
}						t_ambient;

typedef struct 			s_scene
{
	s_objects	objs;
	s_lights	lights;
	s_cameras	cams;
	s_ambient	amb;
	size_t 		valid;
}						t_scene;

#endif