/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:19:22 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 15:19:24 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	t_list_obj	*tr_assign_f(char **p1, char **p2, char **p3, char **col)
{
	t_list_obj		*elem;
	t_obj			*tr;

	if (!(tr = (t_obj*)malloc(sizeof(t_obj))))
		return (0);
	if (!(elem = (t_list_obj*)malloc(sizeof(t_list_obj))))
	{
		free4(tr, 0, 0, 0);
		return (0);
	}
	vector_assign(&tr->p1, p1);
	vector_assign(&tr->p2, p2);
	vector_assign(&tr->p3, p3);
	vector_assign(&tr->color, col);
	if (!(0 <= tr->color.x && 0 <= tr->color.y && 0 <= tr->color.z
	&& tr->color.x <= 255 && tr->color.y <= 255 && tr->color.z <= 255))
	{
		free4((void*)tr, (void*)elem, 0, 0);
		return (0);
	}
	return (elem_assign_r(elem, tr, TR));
}

static	t_list_obj	*tr_assign_t(char **p1, char **p2, char **p3, char **col)
{
	int		i;
	char	*base;

	base = "-0123456789";
	i = 0;
	while (p1[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (p2[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (p3[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (col[i])
		i++;
	if (i != 3)
		return (0);
	return (tr_assign_f(p1, p2, p3, col));
}

static	void		tr_assign_s(char **srcs, t_scene *scene)
{
	char		**p1;
	char		**p2;
	char		**p3;
	char		**col;
	t_list_obj	*elem;

	if (!(p1 = ft_split(srcs[1], ',')))
		scene->objs.valid = 0;
	if (!(p2 = ft_split(srcs[2], ',')))
		scene->objs.valid = 0;
	if (!(p3 = ft_split(srcs[3], ',')))
		scene->objs.valid = 0;
	if (!(col = ft_split(srcs[4], ',')))
		scene->objs.valid = 0;
	if (scene->objs.valid && (elem = tr_assign_t(p1, p2, p3, col)))
		ft_lstadd_back((void*)&scene->objs.lst_objs, (void*)elem);
	else
		scene->objs.valid = 0;
	clr_src(p1, p2, p3, col);
}

static	void		tr_assign_fst(char **srcs, t_scene *scene)
{
	size_t		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 5)
	{
		scene->objs.valid = 0;
		return ;
	}
	tr_assign_s(srcs, scene);
}

void				tr_handle(char const *buf, t_scene *scene, size_t cap)
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
	if (scene->objs.lone_tr || !((ft_strnstr(srcs[0], "tr", 2))
	|| ft_strnstr(srcs[0], "Tr", 2)))
		scene->objs.valid = 0;
	if (cap)
		scene->objs.lone_tr = 1;
	else
		scene->objs.nolone_tr = 1;
	if (scene->objs.lone_tr && scene->objs.nolone_tr)
		scene->objs.valid = 0;
	tr_assign_fst(srcs, scene);
	if (!scene->objs.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
