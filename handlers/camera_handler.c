/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:35:19 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 18:35:20 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	cam_assign_t(char **loc, char *fov, char **dir, t_scene *scene)
{
	t_list_cam		*elem;
	t_cam			*cam;

	if (!(cam = (t_cam*)malloc(sizeof(t_lt))))
	{
		scene->cams.valid = 0;
		return ;
	}
	if (!(elem = (t_list_cam*)malloc(sizeof(t_list_cam))))
	{
		free(cam);
		scene->cams.valid = 0;
		return ;
	}
	vector_assign(&cam->point, loc);
	cam->fov = ft_atof(fov);
	vector_assign(&cam->dir, dir);
	cam->dir = normalize(cam->dir);
	if (!(0 <= fabs(cam->dir.x) && 0 <= fabs(cam->dir.y)
	&& 0 <= fabs(cam->dir.z) && fabs(cam->dir.x) <= 1 && fabs(cam->dir.y) <= 1
	&& fabs(cam->dir.z) <= 1 && 0 <= cam->fov && cam->fov <= 180))
		scene->cams.valid = 0;
	elem->content = cam;
	ft_tlstadd_back(&scene->cams.lst_cams, elem);
}

static	void	cam_assign_s(char **loc, char **srcs, char **dir, t_scene *sc)
{
	int		i;
	char	*base;
	char	*fov;

	if (sc->cams.valid)
	{
		base = "-0123456789";
		i = 0;
		while (loc[i])
			i++;
		if (i != 3)
			sc->cams.valid = 0;
		i = 0;
		while (dir[i])
			i++;
		if (i != 3)
			sc->cams.valid = 0;
		if (!sc->cams.valid)
			return ;
		fov = srcs[3];
		cam_assign_t(loc, fov, dir, sc);
	}
}

static	void	cam_assign_f(char **srcs, t_scene *scene)
{
	char	**loc;
	char	**dir;

	if (!(loc = ft_split(srcs[1], ',')))
		scene->cams.valid = 0;
	if (!(dir = ft_split(srcs[2], ',')))
		scene->cams.valid = 0;
	cam_assign_s(loc, srcs, dir, scene);
	clr_src(loc, dir, 0, 0);
}

static	void	cam_to_handle(char **srcs, t_scene *scene)
{
	int		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 4)
	{
		scene->cams.valid = 0;
		return ;
	}
	cam_assign_f(srcs, scene);
}

void			camera_handle(char const *buf, t_scene *scene, size_t cap)
{
	char	**srcs;

	if (*(buf + 1) != ' ' || !(ft_finddict("0123456789-., ", buf + 1)))
	{
		scene->valid = 0;
		return ;
	}
	if (!(srcs = ft_split(buf, ' ')))
	{
		scene->valid = 0;
		return ;
	}
	if (scene->cams.lone_camera || (!ft_finddict("Cc", srcs[0])))
		scene->cams.valid = 0;
	if (cap)
		scene->cams.lone_camera = 1;
	else
		scene->cams.nolone_camera = 1;
	if (scene->cams.nolone_camera && scene->cams.lone_camera)
		scene->amb.valid = 0;
	cam_to_handle(srcs, scene);
	if (!scene->cams.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
