/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tlst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:30:28 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 19:30:29 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		ft_tlstadd_back(t_list_cam **lst, t_list_cam *new)
{
	t_list_cam		*cur;

	cur = *lst;
	if (cur)
	{
		while (cur->next && cur->num < cur->next->num)
			cur = cur->next;
		cur->next = new;
		(*lst)->prev = new;
		new->prev = cur;
		new->next = *lst;
		new->num = g_camnum++;
	}
	else
	{
		*lst = new;
		new->prev = *lst;
		new->next = *lst;
		new->num = g_camnum++;
	}
}
