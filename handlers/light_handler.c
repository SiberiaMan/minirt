/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:45:34 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 12:45:35 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	light_assign_t(char **loc, char *k, char **col, t_scene *scene)
{
	t_list_l	*elem;
	t_lt		*light;

	if (!(light = (t_lt*)malloc(sizeof(t_lt))))
	{
		scene->lights.valid = 0;
		return ;
	}
	if (!(elem = (t_list_l*)malloc(sizeof(t_list))))
	{
		free(light);
		scene->lights.valid = 0;
		return ;
	}
	vector_assign(&light->point, loc);
	light->intensity = ft_atof(k);
	vector_assign(&light->color, col);
	if (!(0 <= light->color.x && 0 <= light->color.y && 0 <= light->color.z
		&& light->color.x <= 255 && light->color.y <= 255 && light->color.z
		<= 255 && 0 <= light->intensity && light->intensity <= 1))
		scene->lights.valid = 0;
	elem->content = light;
	elem->next = 0;
	ft_lstadd_back((void*)&scene->lights.lst_lts, (void*)elem);
}

static	void	light_assign_s(char **loc, char **srcs, char **col, t_scene *sc)
{
	int		i;
	char	*base;
	char	*k;

	if (sc->lights.valid)
	{
		base = "-0123456789";
		i = 0;
		while (loc[i])
			i++;
		if (i != 3)
			sc->lights.valid = 0;
		i = 0;
		while (col[i])
			i++;
		if (i != 3)
			sc->lights.valid = 0;
		if (!sc->lights.valid)
			return ;
		k = srcs[2];
		light_assign_t(loc, k, col, sc);
	}
}

static	void	light_assign_f(char **srcs, t_scene *scene)
{
	char	**loc;
	char	**col;

	loc = 0;
	col = 0;
	if (!(loc = ft_split(srcs[1], ',')))
		scene->lights.valid = 0;
	if (!(col = ft_split(srcs[3], ',')))
		scene->lights.valid = 0;
	light_assign_s(loc, srcs, col, scene);
	clr_src(loc, col, 0, 0);
}

static	void	l_to_handle(char **srcs, t_scene *scene)
{
	int		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 4)
	{
		scene->lights.valid = 0;
		return ;
	}
	light_assign_f(srcs, scene);
}

void			light_handle(char const *buf, t_scene *scene, size_t cap)
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
	if (scene->lights.lone_light || (!ft_finddict("Ll", srcs[0])))
		scene->lights.valid = 0;
	if (cap)
		scene->lights.lone_light = 1;
	else
		scene->lights.nolone_light = 1;
	if (scene->lights.nolone_light && scene->lights.lone_light)
		scene->lights.valid = 0;
	l_to_handle(srcs, scene);
	if (!scene->lights.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
