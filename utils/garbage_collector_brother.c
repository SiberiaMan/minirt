/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_brother.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:21:38 by dchani            #+#    #+#             */
/*   Updated: 2021/02/15 18:21:39 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clear_project(t_scene *scene, t_vars *vars)
{
	if (vars->mlx)
	{
		free(vars->mlx);
		vars->mlx = 0;
	}
	if (vars->img.img)
	{
		free(vars->img.img);
		vars->img.img = 0;
	}
	if (vars->win)
	{
		free(vars->win);
		vars->win = 0;
	}
	clear_scene1(scene);
}
