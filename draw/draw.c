/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:58:26 by dchani            #+#    #+#             */
/*   Updated: 2021/02/15 18:50:04 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void			get_window_size(void *mlx_ptr, size_t *width,
size_t *height)
{
	size_t		w;
	size_t		h;

	w = 0;
	h = 0;
	mlx_get_screen_size(mlx_ptr, (int*)&w, (int*)&h);
	if (*width > w)
		*width = w;
	if (*height > h)
		*height = h;
}

static	void		ray_tracing(t_vars *vars, t_scene *scene, double fov)
{
	size_t			i;
	size_t			j;
	double			x;
	double			y;
	t_vec3f			rgb;

	j = 0;
	while (j < scene->height)
	{
		i = 0;
		while (i < scene->width)
		{
			x = (2 * (i + 0.5) / scene->width - 1) * tan(fov / 2.) *
			scene->width / scene->height;
			y = -(2 * (j + 0.5) / scene->height - 1) * tan(fov / 2.);
			rgb = cast_ray((t_vec3f){0, 0, 0}, normalize((t_vec3f){x, y, -1}),
			scene);
			my_mlx_pixel_put(&(vars->img), i, j, create_trgb(0, (int)rgb.x,
			(int)rgb.y, (int)rgb.z));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

static	int			depend(int keycode, t_params *p)
{
	double		fov;

	if (keycode == 2)
	{
		p->num++;
		rotation(&(p->scene), p->num, &fov, 0);
		ray_tracing(p->vars, p->scene, (fov / 180) * M_PI);
		rotation(&(p->scene), p->num, &fov, 1);
	}
	if (keycode == 0)
	{
		p->num--;
		rotation(&(p->scene), p->num, &fov, 0);
		ray_tracing(p->vars, p->scene, (fov / 180) * M_PI);
		rotation(&(p->scene), p->num, &fov, 1);
	}
	if (keycode == 53)
	{
		clear_project(p->scene, p->vars);
		write(0, "Finished\n", 9);
		exit(0);
	}
	if (keycode == 13)
		export_bmp(p->scene, p->vars);
	return (0);
}

static	void		start_ray_tracing_2(t_vars *vars, t_scene *scene)
{
	double		fov;
	t_params	p;

	p.scene = scene;
	p.vars = vars;
	p.num = 0;
	if (!(vars->img.addr = mlx_get_data_addr(vars->img.img,
	&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian)))
	{
		perror("Error\n");
		clear_project(scene, vars);
		exit(1);
	}
	rotation(&scene, p.num, &fov, 0);
	ray_tracing(vars, scene, (fov / 180) * M_PI);
	rotation(&scene, p.num, &fov, 1);
	if (scene->sv)
	{
		export_bmp(p.scene, p.vars);
		close_win(&p);
	}
	mlx_hook(vars->win, 2, 1L << 0, depend, &p);
	mlx_hook(vars->win, 17, 0, close_win, &p);
	mlx_loop(vars->mlx);
}

void				start_ray_tracing_1(t_scene *scene)
{
	t_vars		vars;

	vars_init(&vars);
	if (!(vars.mlx = mlx_init()))
	{
		perror("Error\n");
		clear_scene1(scene);
		exit(1);
	}
	get_window_size(vars.mlx, &scene->width, &scene->height);
	if (!(vars.win = mlx_new_window(vars.mlx, scene->width, scene->height,
	"minirt")))
	{
		perror("Error\n");
		clear_project(scene, &vars);
		exit(1);
	}
	if (!(vars.img.img = mlx_new_image(vars.mlx, scene->width, scene->height)))
	{
		perror("Error\n");
		clear_project(scene, &vars);
		exit(1);
	}
	start_ray_tracing_2(&vars, scene);
}
