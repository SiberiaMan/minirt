/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:21:49 by dchani            #+#    #+#             */
/*   Updated: 2020/11/24 20:45:39 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene		init_scene(void)
{
	t_scene		scene;
	t_objects 	objects;
	t_cameras	cameras;
	t_ambient 	ambient;
	t_lights 	lights;

	objects.valid = 1;
	objects.lst_objs = 0;
	cameras.valid = 1;
	cameras.lst_cams = 0;
	ambient.valid = 1;
	ambient.lst_amb = 0;
	lights.valid = 1;
	lights.lst_lts = 0;
	scene = (t_scene){
			.objs = objects,
			.lights = lights,
			.cams = cameras,
			.amb = ambient,
			.valid = 1
	};

	return (scene);
}

static void			check_line_second(char *buf, t_scene *scene, char *ptr)
{
	if ((ptr = ft_strnstr(buf, "Pl", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		plane_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "pl", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		plane_handle(buf, scene, 0);
	if ((ptr = ft_strnstr(buf, "Cy", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		cyl_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "cy", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		cyl_handle(buf, scene, 0);
	if ((ptr = ft_strnstr(buf, "Tr", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		tr_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "tr", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		tr_handle(buf, scene, 0);
	if ((ptr = ft_strnstr(buf, "Sq", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		tr_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "sq", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		tr_handle(buf, scene, 0);
}

static	void		check_line_first(char *buf, t_scene *scene)
{
	char	*ptr;

	if ((ptr = ft_strnstr(buf, "L", 1)) && *(ptr + 1)
		&& *(ptr + 1) == ' ')
		light_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "l", 1)) && *(ptr + 1)
		&& *(ptr + 1) == ' ')
		light_handle(buf, scene, 0);
	if ((ptr = ft_strnstr(buf, "C", 1)) && *(ptr + 1)
		&& *(ptr + 1) == ' ')
		camera_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "c", 1)) && *(ptr + 1)
		&& *(ptr + 1) == ' ')
		camera_handle(buf, scene, 0);
	if ((ptr = ft_strnstr(buf, "A", 1)) && *(ptr + 1)
		&& *(ptr + 1) == ' ')
		ambient_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "Sp", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		sphere_handle(buf, scene, 1);
	if ((ptr = ft_strnstr(buf, "sp", 1)) && *(ptr + 2)
		&& *(ptr + 2) == ' ')
		sphere_handle(buf, scene, 0);
	check_line_second(buf, scene, ptr);
}

t_scene				*parse(int argc, char **argv)
{
	int 	fd;
	int 	check;
	char	*buf;
	int 	res;
	t_scene scene;

	scene = init_scene();
	fd = open(argv[1], O_RDONLY);
	if (!fd || !(buf = malloc(g_buf)))
	{
		perror("Error: ");
		return 0;
	}
	while ((check = get_next_line(fd, &buf)))
	{
		if (check == -1)
		{
			perror("Error: ");
			return 0;
		}
	}
}
