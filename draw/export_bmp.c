/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 20:51:53 by dchani            #+#    #+#             */
/*   Updated: 2021/02/16 20:51:54 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	void	fill_image(char **buf, t_data *data, int w, int h)
{
	int		i;
	int		j;
	int		k;

	i = H_SIZE;
	while (h--)
	{
		k = -1;
		while (++k < w)
		{
			j = (k * (data->bits_per_pixel / 8) + h * (data->line_length));
			*(*buf + i++) = *(data->addr + j++);
			*(*buf + i++) = *(data->addr + j++);
			*(*buf + i++) = *(data->addr + j);
		}
	}
	write(0, "SHOT!!!\n", 8);
}

static	void	header_bmp(char **buf, int size, int w, int h)
{
	*(unsigned short*)*buf = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int*)(*buf + 2) = size + H_SIZE;
	*(unsigned int*)(*buf + 6) = 0u;
	*(unsigned char*)(*buf + 10) = H_SIZE;
	*(unsigned int*)(*buf + 14) = H_SIZE - 14;
	*(unsigned int*)(*buf + 18) = w;
	*(unsigned int*)(*buf + 22) = h;
	*(unsigned short*)(*buf + 26) = 1;
	*(unsigned short*)(*buf + 28) = 24;
	*(unsigned int*)(*buf + 30) = 0;
	*(unsigned int*)(*buf + 34) = (unsigned int)size;
	*(unsigned int*)(*buf + 38) = 3780;
	*(unsigned int*)(*buf + 42) = 3780;
	*(unsigned int*)(*buf + 46) = 0;
	*(unsigned int*)(*buf + 50) = 0;
}

void			export_bmp(t_scene *scene, t_vars *vars)
{
	int		fd;
	int		size;
	char	*buf;

	size = scene->width * scene->height * 3;
	if (!(buf = malloc(size + H_SIZE)))
	{
		perror("Error\n");
		clear_project(scene, vars);
		exit(0);
	}
	header_bmp(&buf, size, scene->width, scene->height);
	fill_image(&buf, &vars->img, scene->width, scene->height);
	if ((fd = open("image.bmp", O_CREAT | O_TRUNC | O_RDWR, 0777)) <= 0)
	{
		free(buf);
		clear_project(scene, vars);
		perror("Error\n");
		exit(0);
	}
	write(fd, buf, (size + H_SIZE));
	free(buf);
	close(fd);
}
