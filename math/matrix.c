/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:14:11 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 20:14:13 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_matrix	matrix3_init(t_vec3f v1, t_vec3f v2, t_vec3f v3)
{
	return ((t_matrix) {
		.v1 = v1,
		.v2 = v2,
		.v3 = v3
	});
}

t_vec3f		vec_mul_m(t_vec3f v, t_matrix m)
{
	return ((t_vec3f) {
		v.x * m.v1.x + v.y * m.v2.x + v.z * m.v3.x,
		v.x * m.v1.y + v.y * m.v2.y + v.z * m.v3.y,
		v.x * m.v1.z + v.y * m.v2.z + v.z * m.v3.z
	});
}

t_matrix	transpose_matrix3(t_matrix m)
{
	return ((t_matrix) {
			(t_vec3f){
				.x = m.v1.x,
				.y = m.v2.x,
				.z = m.v3.x
			},
			(t_vec3f) {
				.x = m.v1.y,
				.y = m.v2.y,
				.z = m.v3.y
			},
			(t_vec3f) {
				.x = m.v1.z,
				.y = m.v2.z,
				.z = m.v3.z
			}
	});
}

double		det3(t_matrix m)
{
	return (m.v1.x * (m.v2.y * m.v3.z - m.v2.z * m.v3.y) - m.v1.y * (m.v2.x *
	m.v3.z - m.v2.z * m.v3.x) + m.v1.z * (m.v2.x * m.v3.y - m.v2.y * m.v3.x));
}

t_matrix	inv_mx3(t_matrix m)
{
	t_matrix	trans_m;
	t_matrix	res_m;
	double		d;

	trans_m = transpose_matrix3(m);
	d = det3(m);
	res_m.v1.x = trans_m.v2.y * trans_m.v3.z - trans_m.v2.z * trans_m.v3.y;
	res_m.v1.y = -(trans_m.v2.x * trans_m.v3.z - trans_m.v2.z * trans_m.v3.x);
	res_m.v1.z = trans_m.v2.x * trans_m.v3.y - trans_m.v2.y * trans_m.v3.x;
	res_m.v2.x = -(trans_m.v1.y * trans_m.v3.z - trans_m.v1.z * trans_m.v3.y);
	res_m.v2.y = trans_m.v1.x * trans_m.v3.z - trans_m.v1.z * trans_m.v3.x;
	res_m.v2.z = -(trans_m.v1.x * trans_m.v3.y - trans_m.v1.y * trans_m.v3.x);
	res_m.v3.x = trans_m.v1.y * trans_m.v2.z - trans_m.v1.z * trans_m.v2.y;
	res_m.v3.y = -(trans_m.v1.x * trans_m.v2.z - trans_m.v1.z * trans_m.v2.x);
	res_m.v3.z = trans_m.v1.x * trans_m.v2.y - trans_m.v1.y * trans_m.v2.x;
	res_m.v1 = mul(res_m.v1, 1 / d);
	res_m.v2 = mul(res_m.v2, 1 / d);
	res_m.v3 = mul(res_m.v3, 1 / d);
	return (res_m);
}
