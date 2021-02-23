/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:19:42 by dchani            #+#    #+#             */
/*   Updated: 2021/02/08 16:19:44 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			free4(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr1)
	{
		free(ptr1);
		ptr1 = 0;
	}
	if (ptr2)
	{
		free(ptr2);
		ptr2 = 0;
	}
	if (ptr3)
	{
		free(ptr3);
		ptr3 = 0;
	}
	if (ptr4)
	{
		free(ptr4);
		ptr4 = 0;
	}
}

static void		free_src(char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		free(src[i]);
		src[i] = 0;
		i++;
	}
	free(src);
}

void			clr_src(char **srcs1, char **srcs2, char **srcs3, char **srcs4)
{
	if (srcs1)
		free_src(srcs1);
	if (srcs2)
		free_src(srcs2);
	if (srcs3)
		free_src(srcs3);
	if (srcs4)
		free_src(srcs4);
}

static	void	clear_scene2(t_scene *scene)
{
	t_list_cam	*cam;
	t_list_cam	*cur1;
	t_list_l	*light;
	t_list_l	*cur2;

	cam = scene->cams.lst_cams;
	while (cam && cam->content)
	{
		cur1 = cam->next;
		free(cam->content);
		cam->content = 0;
		cam = cur1;
	}
	light = scene->lights.lst_lts;
	while (light)
	{
		cur2 = light->next;
		free(light->content);
		free(light);
		light = cur2;
	}
	free(scene);
}

void			clear_scene1(t_scene *scene)
{
	t_list_obj	*obj;
	t_list_obj	*cur1;
	t_list_amb	*amb;
	t_list_amb	*cur2;

	if (scene)
	{
		obj = scene->objs.lst_objs;
		while (obj)
		{
			cur1 = obj->next;
			free(obj->content);
			free(obj);
			obj = cur1;
		}
		amb = scene->amb.lst_amb;
		while (amb)
		{
			cur2 = amb->next;
			free(amb->content);
			free(amb);
			amb = cur2;
		}
		clear_scene2(scene);
	}
}
