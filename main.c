/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:49:34 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 17:49:36 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int		main(int argc, char **argv)
{
	t_scene		*scene;

	if (argc == 1)
		write(0, "Error\nNo given files", 20);
	else if (check_format(argv[1]) && (scene = parse(argv)))
	{
		if (argc == 3 && ft_strnstr(argv[2], "--save", 6))
			scene->sv = 1;
		else if (argc > 3 || (argc == 3 && !ft_strnstr(argv[2], "--save", 6)))
		{
			write(0, "Error\nWrong arguments\n", 23);
			clear_scene1(scene);
			return (0);
		}
		if (!scene->valid)
		{
			write(0, "Error\nWrong .rt format", 22);
			clear_scene1(scene);
		}
		else
			start_ray_tracing_1(scene);
	}
	else
		write(0, "Error\nIt's not .rt file :(\n", 27);
	return (0);
}
