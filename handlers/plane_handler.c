/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:09:42 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 13:09:43 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	pl_assign_t(char **c, char **n, char **col, t_scene *scene)
{
	t_list_obj		*elem;
	t_obj			*plane;

	if (!(plane = (t_obj*)malloc(sizeof(t_obj))))
	{
		scene->objs.valid = 0;
		return ;
	}
	if (!(elem = (t_list_obj*)malloc(sizeof(t_list_obj))))
	{
		free(plane);
		scene->objs.valid = 0;
		return ;
	}
	vector_assign(&plane->center, c);
	vector_assign(&plane->normal, n);
	vector_assign(&plane->color, col);
	if (!(0 <= plane->color.x && 0 <= plane->color.y && 0 <= plane->color.z
	&& plane->color.x <= 255 && plane->color.y <= 255 && plane->color.z <= 255
	&& 0 <= plane->d && 0 <= fabs(plane->normal.x) && 0 <= fabs(plane->normal.y)
	&& 0 <= fabs(plane->normal.z) && fabs(plane->normal.x) <= 1 &&
	fabs(plane->normal.y) <= 1 && fabs(plane->normal.z) <= 1))
		scene->objs.valid = 0;
	elem_assign(elem, plane, PL);
	ft_lstadd_back((void*)&scene->objs.lst_objs, (void*)elem);
}

static	void	pl_assign_s(char **c, char **n, char **col, t_scene *sc)
{
	int		i;
	char	*base;

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
		i = 0;
		while (n[i])
			i++;
		if (i != 3)
			sc->objs.valid = 0;
		if (!sc->objs.valid)
			return ;
		pl_assign_t(c, n, col, sc);
	}
}

static	void	pl_assign_f(char **srcs, t_scene *scene)
{
	char	**c;
	char	**col;
	char	**normal;

	if (!(c = ft_split(srcs[1], ',')))
		scene->objs.valid = 0;
	if (!(normal = ft_split(srcs[2], ',')))
		scene->objs.valid = 0;
	if (!(col = ft_split(srcs[3], ',')))
		scene->objs.valid = 0;
	pl_assign_s(c, normal, col, scene);
	clr_src(c, col, normal, 0);
}

static	void	pl_to_handle(char **srcs, t_scene *scene)
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
	pl_assign_f(srcs, scene);
}

void			plane_handle(char const *buf, t_scene *scene, size_t cap)
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
	if (scene->objs.lone_pl || !((ft_strnstr(srcs[0], "pl", 2))
	|| ft_strnstr(srcs[0], "Pl", 2)))
		scene->objs.valid = 0;
	if (cap)
		scene->objs.lone_pl = 1;
	else
		scene->objs.nolone_pl = 1;
	if (scene->objs.lone_pl && scene->objs.nolone_pl)
		scene->objs.valid = 0;
	pl_to_handle(srcs, scene);
	if (!scene->objs.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
