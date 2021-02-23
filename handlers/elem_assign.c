/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:55:48 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 12:55:50 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			elem_assign(t_list_obj *elem, t_obj *obj, t_names name)
{
	elem->content = obj;
	elem->content->name = name;
	elem->content->number = g_num++;
	elem->next = 0;
}

t_list_obj		*elem_assign_r(t_list_obj *elem, t_obj *obj, t_names name)
{
	elem->content = obj;
	elem->content->name = name;
	elem->content->number = g_num++;
	elem->next = 0;
	return (elem);
}
