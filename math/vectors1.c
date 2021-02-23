/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:03:12 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 20:03:13 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3f		sub(t_vec3f u, t_vec3f v)
{
	return ((t_vec3f) {
		u.x - v.x,
			u.y - v.y,
			u.z - v.z
	});
}

t_vec3f		add(t_vec3f u, t_vec3f v)
{
	return ((t_vec3f) {
			u.x + v.x,
			u.y + v.y,
			u.z + v.z
	});
}

t_vec3f		mul(t_vec3f u, double v)
{
	return ((t_vec3f) {
			u.x * v,
			u.y * v,
			u.z * v
	});
}

double		dot(t_vec3f u, t_vec3f v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3f		cross(t_vec3f u, t_vec3f v)
{
	return ((t_vec3f) {
			u.y * v.z - u.z * v.y,
		-(u.x * v.z - u.z * v.x),
			u.x * v.y - u.y * v.x
	});
}
