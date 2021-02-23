/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:54:47 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 14:54:48 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	t_list_obj	*cyl_assign_f(char **c, char **n, char **col, char **buf)
{
	t_list_obj		*elem;
	t_obj			*cyl;

	if (!(cyl = (t_obj*)malloc(sizeof(t_obj))))
		return (0);
	if (!(elem = (t_list_obj*)malloc(sizeof(t_list_obj))))
	{
		free4(cyl, 0, 0, 0);
		return (0);
	}
	vector_assign(&cyl->center, c);
	vector_assign(&cyl->normal, n);
	cyl->normal = normalize(cyl->normal);
	vector_assign(&cyl->color, col);
	cyl->d = ft_atof(buf[0]);
	cyl->side = ft_atof(buf[1]);
	if (!(color_check(&cyl->color) && normal_check(&cyl->normal)
	&& 0 <= cyl->d && cyl->side >= 0 && cyl->d >= 0))
	{
		free4((void*)cyl, (void*)elem, 0, 0);
		return (0);
	}
	return (elem_assign_r(elem, cyl, CY));
}

static	t_list_obj	*cyl_assign_t(char **c, char **n, char **col, char **buf)
{
	int		i;
	char	*base;

	base = "-0123456789";
	i = 0;
	while (c[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (col[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (n[i])
		i++;
	if (i != 3)
		return (0);
	return (cyl_assign_f(c, n, col, buf));
}

static	void		cyl_assign_s(char **srcs, t_scene *scene)
{
	char		**c;
	char		**col;
	char		**normal;
	char		*buf[3];
	t_list_obj	*elem;

	if (!(c = ft_split(srcs[1], ',')))
		scene->objs.valid = 0;
	if (!(normal = ft_split(srcs[2], ',')))
		scene->objs.valid = 0;
	if (!(col = ft_split(srcs[3], ',')))
		scene->objs.valid = 0;
	if (!(ft_finddict("0123456789.", srcs[4])) ||
		!(ft_finddict("0123456789.", srcs[5])))
		scene->objs.valid = 0;
	buf[0] = srcs[4];
	buf[1] = srcs[5];
	if (scene->objs.valid && (elem = cyl_assign_t(c, normal, col, buf)))
		ft_lstadd_back((void*)&scene->objs.lst_objs, (void*)elem);
	else
		scene->objs.valid = 0;
	clr_src(c, col, normal, 0);
}

static	void		cyl_assign_fst(char **srcs, t_scene *scene)
{
	size_t		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 6)
	{
		scene->objs.valid = 0;
		return ;
	}
	cyl_assign_s(srcs, scene);
}

void				cyl_handle(char const *buf, t_scene *scene, size_t cap)
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
	if (scene->objs.lone_cy || !((ft_strnstr(srcs[0], "cy", 2))
	|| ft_strnstr(srcs[0], "Cy", 2)))
		scene->objs.valid = 0;
	if (cap)
		scene->objs.lone_cy = 1;
	else
		scene->objs.nolone_cy = 1;
	if (scene->objs.lone_cy && scene->objs.nolone_cy)
		scene->objs.valid = 0;
	cyl_assign_fst(srcs, scene);
	if (!scene->objs.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
