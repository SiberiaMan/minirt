/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:51:29 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 17:51:30 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	amb_assign_t(char **loc, char *k, t_scene *scene)
{
	t_list_amb		*elem;
	t_amb			*amb;

	if (!(amb = (t_amb*)malloc(sizeof(t_amb))))
	{
		scene->amb.valid = 0;
		return ;
	}
	if (!(elem = (t_list_amb*)malloc(sizeof(t_list_amb))))
	{
		free(amb);
		scene->amb.valid = 0;
		return ;
	}
	vector_assign(&amb->color, loc);
	amb->k = ft_atof(k);
	if (!(0 <= amb->color.x && 0 <= amb->color.y && 0 <= amb->color.z
	&& amb->color.x <= 255 && amb->color.y <= 255 && amb->color.z <= 255
	&& 0 <= amb->k && amb->k <= 1))
		scene->amb.valid = 0;
	elem->content = amb;
	elem->next = 0;
	ft_lstadd_back((void*)&scene->amb.lst_amb, (void*)elem);
}

static	void	amb_assign_s(char **loc, char **srcs, t_scene *scene)
{
	int		i;
	char	*base;
	char	*k;

	base = "-0123456789";
	i = 0;
	while (loc[i])
		i++;
	if (i != 3)
		scene->amb.valid = 0;
	if (!scene->amb.valid)
		return ;
	k = srcs[1];
	amb_assign_t(loc, k, scene);
}

static	void	amb_assign_f(char **srcs, t_scene *scene)
{
	char	**loc;
	int		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 3)
	{
		scene->amb.valid = 0;
		return ;
	}
	if (!(loc = ft_split(srcs[2], ',')))
		return ;
	amb_assign_s(loc, srcs, scene);
	clr_src(loc, 0, 0, 0);
}

void			ambient_handle(char const *buf, t_scene *scene, size_t cap)
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
	if (scene->amb.lone_ambient || (!ft_finddict("A", srcs[0])))
		scene->amb.valid = 0;
	if (cap)
		scene->amb.lone_ambient = 1;
	else
		scene->amb.nolone_ambient = 1;
	if (scene->amb.nolone_ambient && scene->amb.lone_ambient)
		scene->amb.valid = 0;
	amb_assign_f(srcs, scene);
	if (!scene->amb.valid)
		scene->valid = 0;
	clr_src(srcs, 0, 0, 0);
}
