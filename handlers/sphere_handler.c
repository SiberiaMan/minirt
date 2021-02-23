/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:27:26 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 20:27:50 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	sp_assign_t(char **c, char *d, char **col, t_scene *scene)
{
	t_list_obj		*elem;
	t_obj			*sphere;

	if (!(sphere = (t_obj*)malloc(sizeof(t_obj))))
	{
		scene->objs.valid = 0;
		return ;
	}
	if (!(elem = (t_list_obj*)malloc(sizeof(t_list_obj))))
	{
		free(sphere);
		scene->objs.valid = 0;
		return ;
	}
	vector_assign(&sphere->center, c);
	sphere->d = ft_atof(d);
	vector_assign(&sphere->color, col);
	if (!(0 <= sphere->color.x && 0 <= sphere->color.y && 0 <= sphere->color.z
	&& sphere->color.x <= 255 && sphere->color.y <= 255
	&& sphere->color.z <= 255 && 0 <= sphere->d))
		scene->objs.valid = 0;
	elem_assign(elem, sphere, SP);
	ft_lstadd_back((void*)&scene->objs.lst_objs, (void*)elem);
}

static	void	sp_assign_s(char **c, char **srcs, char **col, t_scene *sc)
{
	int		i;
	char	*base;
	char	*d;

	if (sc->objs.valid)
	{
		base = "-0123456789";
		i = 0;
		while (c[i])
			i++;
		if (i != 3)
			sc->objs.valid = 0;
		i = 0;
		while (col[i])
			i++;
		if (i != 3)
			sc->objs.valid = 0;
		if (!sc->objs.valid)
			return ;
		d = srcs[2];
		sp_assign_t(c, d, col, sc);
	}
}

static	void	sp_assign_f(char **srcs, t_scene *scene)
{
	char	**c;
	char	**col;

	if (!(c = ft_split(srcs[1], ',')))
		scene->objs.valid = 0;
	if (!(col = ft_split(srcs[3], ',')))
		scene->objs.valid = 0;
	sp_assign_s(c, srcs, col, scene);
	clr_src(c, col, 0, 0);
}

static	void	sp_to_handle(char **srcs, t_scene *scene)
{
	int		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 4)
	{
		scene->objs.valid = 0;
		return ;
	}
	sp_assign_f(srcs, scene);
}

void			sphere_handle(char const *buf, t_scene *scene, size_t cap)
{
	char	**srcs;

	if (*(buf + 2) != ' ' || !(ft_finddict("0123456789-., ", buf + 2)))
	{
		scene->valid = 0;
		return ;
	}
	if (!(srcs = ft_split(buf, ' ')))
	{
		scene->valid = 0;
		return ;
	}
	if (scene->objs.lone_sp || !((ft_strnstr(srcs[0], "sp", 2))
		|| ft_strnstr(srcs[0], "Sp", 2)))
		scene->objs.valid = 0;
	if (cap)
		scene->objs.lone_sp = 1;
	else
		scene->objs.nolone_sp = 1;
	if (scene->objs.lone_sp && scene->objs.nolone_sp)
		scene->objs.valid = 0;
	sp_to_handle(srcs, scene);
	if (!scene->objs.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
