/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:57:18 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 18:57:20 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	res_assign_f(char **srcs, t_scene *scene)
{
	double	width;
	double	height;
	int		i;

	i = 0;
	while (srcs[i])
		i++;
	if (i != 3)
	{
		scene->valid = 0;
		return ;
	}
	width = ft_atof(srcs[1]);
	height = ft_atof(srcs[2]);
	scene->width = width;
	scene->height = height;
}

void			res_handle(char const *buf, t_scene *scene, size_t cap)
{
	char	**srcs;

	(void)cap;
	if (*(buf + 1) != ' ' || !(ft_finddict("0123456789. ", buf + 1)))
	{
		scene->valid = 0;
		return ;
	}
	if (!(srcs = ft_split(buf, ' ')))
	{
		scene->valid = 0;
		return ;
	}
	if (scene->is_resolution || scene->cams.lone_camera
	|| (!ft_finddict("R", srcs[0])))
		scene->valid = 0;
	scene->is_resolution = 1;
	res_assign_f(srcs, scene);
	clr_src(srcs, 0, 0, 0);
}
