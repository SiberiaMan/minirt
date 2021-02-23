/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:48:41 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 13:48:43 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	t_list_obj	*sq_assign_t(char **c, char **n, char **col, char *side)
{
	t_list_obj		*elem;
	t_obj			*sq;

	if (!(sq = (t_obj*)malloc(sizeof(t_obj))))
		return (0);
	if (!(elem = (t_list_obj*)malloc(sizeof(t_list_obj))))
	{
		free4(sq, 0, 0, 0);
		return (0);
	}
	vector_assign(&sq->center, c);
	vector_assign(&sq->normal, n);
	sq->normal = normalize(sq->normal);
	vector_assign(&sq->color, col);
	sq->side = ft_atof(side);
	if (!(color_check(&sq->color) && normal_check(&sq->normal)
	&& sq->side >= 0))
	{
		free4((void*)sq, (void*)elem, 0, 0);
		return (0);
	}
	return (elem_assign_r(elem, sq, SQ));
}

static	t_list_obj	*sq_assign_s(char **c, char **n, char **col, char *side)
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
	return (sq_assign_t(c, n, col, side));
}

static	void		sq_assign_f(char **srcs, t_scene *scene)
{
	char		**c;
	char		**col;
	char		**normal;
	t_list_obj	*elem;

	if (!(c = ft_split(srcs[1], ',')))
		scene->objs.valid = 0;
	if (!(normal = ft_split(srcs[2], ',')))
		scene->objs.valid = 0;
	if (!(col = ft_split(srcs[4], ',')))
		scene->objs.valid = 0;
	if (!(ft_finddict("0123456789.", srcs[3])))
		scene->objs.valid = 0;
	if (scene->objs.valid && (elem = sq_assign_s(c, normal, col, srcs[3])))
		ft_lstadd_back((void*)&scene->objs.lst_objs, (void*)elem);
	else
		scene->objs.valid = 0;
	clr_src(c, col, normal, 0);
}

static	void		sq_to_handle(char **srcs, t_scene *scene)
{
	int		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 5)
	{
		scene->objs.valid = 0;
		return ;
	}
	sq_assign_f(srcs, scene);
}

void				square_handle(char const *buf, t_scene *scene, size_t cap)
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
	if (scene->objs.lone_sq || !((ft_strnstr(srcs[0], "sq", 2))
	|| ft_strnstr(srcs[0], "Sq", 2)))
		scene->objs.valid = 0;
	if (cap)
		scene->objs.lone_sq = 1;
	else
		scene->objs.nolone_sq = 1;
	if (scene->objs.lone_sq && scene->objs.nolone_sq)
		scene->objs.valid = 0;
	sq_to_handle(srcs, scene);
	if (!scene->objs.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
