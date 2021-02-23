/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:21:49 by dchani            #+#    #+#             */
/*   Updated: 2020/11/24 20:45:39 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

size_t				check_format(char *argv)
{
	size_t		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '.')
			break ;
		i++;
	}
	if (argv[i] == '.' && argv[i + 1] && argv[i + 1] == 'r' && argv[i + 2]
	&& argv[i + 2] == 't' && (argv[i + 3] == '\0' || argv[i + 3] == ' '
	|| argv[i + 3] == '\n'))
		return (1);
	return (0);
}

static void			check_line_second(char *buf, t_scene *scene, char *ptr)
{
	if ((ptr = ft_strnstr(buf, "Pl", 2)))
		plane_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "pl", 2)))
		plane_handle(buf, scene, 0);
	else if ((ptr = ft_strnstr(buf, "Cy", 2)))
		cyl_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "cy", 2)))
		cyl_handle(buf, scene, 0);
	else if ((ptr = ft_strnstr(buf, "Tr", 2)))
		tr_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "tr", 2)))
		tr_handle(buf, scene, 0);
	else if ((ptr = ft_strnstr(buf, "Sq", 2)))
		square_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "sq", 2)))
		square_handle(buf, scene, 0);
	else if (*buf != '\0')
		scene->valid = 0;
}

static	void		check_line_first(char *buf, t_scene *scene)
{
	char	*ptr;

	if ((ptr = ft_strnstr(buf, "L", 1)))
		light_handle(ptr, scene, 1);
	else if ((ptr = ft_strnstr(buf, "l", 1)))
		light_handle(buf, scene, 0);
	else if ((ptr = ft_strnstr(buf, "A", 1)))
		ambient_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "C", 1)) && *(ptr + 1) && *(ptr + 1) != 'y')
		camera_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "c", 1)) && *(ptr + 1) && *(ptr + 1) != 'y')
		camera_handle(buf, scene, 0);
	else if ((ptr = ft_strnstr(buf, "R", 1)))
		res_handle(buf, scene, 0);
	else if ((ptr = ft_strnstr(buf, "Sp", 2)))
		sphere_handle(buf, scene, 1);
	else if ((ptr = ft_strnstr(buf, "sp", 2)))
		sphere_handle(buf, scene, 0);
	else
		check_line_second(buf, scene, ptr);
}

static	void		check_f(int check, char **buf, t_scene *scene)
{
	if (check == -1)
	{
		free(*buf);
		*buf = 0;
		return ;
	}
	check_line_first(*buf, scene);
	free(*buf);
	*buf = 0;
}

t_scene				*parse(char **argv)
{
	int		fd;
	int		check;
	char	*buf;
	t_scene *scene;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !(scene = (t_scene*)malloc(sizeof(t_scene))))
	{
		perror("Error\n");
		exit(0);
	}
	scene = init_scene(scene);
	while (scene && scene->valid && (check = get_next_line(fd, &buf)))
		check_f(check, &buf, scene);
	if (scene && scene->valid)
		check_f(check, &buf, scene);
	if (buf)
		free(buf);
	if (scene && !scene->is_resolution)
		scene->valid = 0;
	return (scene);
}
