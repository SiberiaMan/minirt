/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:05:06 by dchani            #+#    #+#             */
/*   Updated: 2021/02/15 19:05:13 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "get_next_line.h"
# include "../mlx/mlx.h"
# include "math_operations.h"
# include "draw.h"

# define G_BUFF			500
# define BUFFER_SIZE	1

size_t					g_num;
int						g_camnum;
size_t					g_cums;
size_t					g_intersect;

typedef	struct			s_lt
{
	t_vec3f				point;
	t_vec3f				color;
	double				intensity;
	int					inter;
}						t_lt;

typedef	struct			s_amb
{
	double				k;
	t_vec3f				color;
	size_t				valid;
}						t_amb;

typedef	struct			s_cam
{
	t_vec3f				point;
	t_vec3f				dir;
	double				fov;
	size_t				valid;
}						t_cam;

typedef	enum			e_names
{
	SP = 1, PL = 2, SQ = 3, CY = 4, TR = 5
}						t_names;

typedef	struct			s_obj
{
	t_names				name;
	size_t				number;
	t_vec3f				center;
	t_vec3f				normal;
	double				d;
	double				side;
	t_vec3f				p1;
	t_vec3f				p2;
	t_vec3f				p3;
	t_vec3f				color;
	size_t				valid;
}						t_obj;

typedef	struct			s_list_l
{
	t_lt				*content;
	struct s_list_l		*next;
}						t_list_l;

typedef	struct			s_list_amb
{
	t_amb				*content;
	struct s_list_amb	*next;
}						t_list_amb;

typedef	struct			s_list_cam
{
	t_cam				*content;
	struct s_list_cam	*next;
	struct s_list_cam	*prev;
	int					num;
}						t_list_cam;

typedef	struct			s_list_obj
{
	t_obj				*content;
	struct s_list_obj	*next;

}						t_list_obj;

typedef	struct			s_objects
{
	t_list_obj			*lst_objs;
	size_t				lone_sp;
	size_t				lone_pl;
	size_t				lone_sq;
	size_t				lone_cy;
	size_t				lone_tr;
	size_t				nolone_sp;
	size_t				nolone_pl;
	size_t				nolone_sq;
	size_t				nolone_cy;
	size_t				nolone_tr;
	size_t				valid;
}						t_objects;

typedef	struct			s_lights
{
	t_list_l			*lst_lts;
	size_t				lone_light;
	size_t				nolone_light;
	size_t				valid;
}						t_lights;

typedef	struct			s_cameras
{
	t_list_cam			*lst_cams;
	size_t				lone_camera;
	size_t				nolone_camera;
	size_t				valid;
}						t_cameras;

typedef	struct			s_ambient
{
	t_list_amb			*lst_amb;
	size_t				lone_ambient;
	size_t				nolone_ambient;
	size_t				valid;
}						t_ambient;

typedef	struct			s_scene
{
	t_objects			objs;
	t_lights			lights;
	t_cameras			cams;
	t_ambient			amb;
	size_t				width;
	size_t				height;
	size_t				is_resolution;
	size_t				valid;
	size_t				sv;
}						t_scene;

typedef struct			s_params
{
	t_vars				*vars;
	t_scene				*scene;
	int					num;
}						t_params;

t_scene					*parse(char **argv);
void					vector_assign(t_vec3f *u, char **buf);
void					free4(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
void					clr_src(char **srcs1, char **srcs2, char **srcs3,
char **srcs4);
void					light_handle(char const *buf, t_scene *scene,
size_t cap);
void					init(t_objects *o, t_cameras *c, t_ambient *a,
t_lights *l);
t_scene					*init_scene(t_scene *scene);
void					ambient_handle(char const *buf, t_scene *scene,
size_t cap);
void					camera_handle(char const *buf, t_scene *scene,
size_t cap);
void					res_handle(char const *buf, t_scene *scene,
size_t cap);
void					sphere_handle(char const *buf, t_scene *scene,
size_t cap);
void					elem_assign(t_list_obj *elem, t_obj *obj, t_names name);
t_list_obj				*elem_assign_r(t_list_obj *elem, t_obj *obj, t_names
name);
void					plane_handle(char const *buf, t_scene *scene, size_t
cap);
void					square_handle(char const *buf, t_scene *scene, size_t
cap);
void					cyl_handle(char const *buf, t_scene *scene, size_t cap);
void					tr_handle(char const *buf, t_scene *scene, size_t cap);
size_t					check_format(char *argv);
void					ft_tlstadd_back(t_list_cam **lst, t_list_cam *new);
size_t					plane_intersect(t_vec3f orig, t_vec3f dir,
double *t0, t_obj *obj);
size_t					sphere_intersect(t_vec3f orig, t_vec3f dir,
double *t0, t_obj *obj);
size_t					square_intersect(t_vec3f orig, t_vec3f dir,
double *t0, t_obj *obj);
size_t					cyl_intersect1(t_vec3f o, t_vec3f d,
double *t0, t_obj *ob);
size_t					tr_intersect1(t_vec3f orig, t_vec3f dir,
double *t0, t_obj *obj);
size_t					ray_to_sphere(t_vec3f orig, t_vec3f dir, t_obj *obj,
double *dist_i);
void					sp_matrix(t_obj *obj, t_vec3f dir, t_vec3f point,
t_matrix *m);
size_t					ray_to_plane(t_vec3f orig, t_vec3f dir, t_obj *obj,
double *dist_i);
void					pl_matrix(t_obj *obj, t_vec3f point, t_matrix *m);
size_t					ray_to_tr(t_vec3f orig, t_vec3f dir, t_obj *obj,
double *dist_i);
void					tr_matrix(t_obj *obj, t_vec3f point, t_matrix *m);
size_t					ray_to_cyl(t_vec3f orig, t_vec3f dir, t_obj *obj,
double *dist_i);
void					cy_matrix(t_obj *obj, t_vec3f dir, t_vec3f point,
t_matrix *m);
size_t					ray_to_sq(t_vec3f orig, t_vec3f dir, t_obj *obj,
double *dist_i);
void					sq_matrix(t_obj *obj, t_vec3f point, t_matrix *m);
t_vec3f					cast_ray(t_vec3f orig, t_vec3f dir,
t_scene *scene);
void					rotation(t_scene **scene, int num, double *fov,
size_t pos);
void					rotate_objects_back(t_scene **scene, double dg_y,
double dg_x, t_vec3f loc);
void					start_ray_tracing_1(t_scene *scene);
void					clear_scene1(t_scene *scene);
void					clear_project(t_scene *scene, t_vars *vars);
void					vars_init(t_vars *vars);
size_t					normal_check(t_vec3f *normal);
size_t					color_check(t_vec3f *color);
void					export_bmp(t_scene *scene, t_vars *vars);
int						close_win(t_params *p);

#endif
