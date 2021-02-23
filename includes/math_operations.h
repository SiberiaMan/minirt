/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operations                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:21:36 by dchani            #+#    #+#             */
/*   Updated: 2021/02/11 16:22:11 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_OPERATIONS_H
# define MATH_OPERATIONS_H

# include "minirt.h"

typedef struct			s_vec3f
{
	double				x;
	double				y;
	double				z;
}						t_vec3f;

typedef struct			s_matrix
{
	t_vec3f				v1;
	t_vec3f				v2;
	t_vec3f				v3;
}						t_matrix;

t_matrix				matrix3_init(t_vec3f v1, t_vec3f v2, t_vec3f v3);
t_vec3f					vec_mul_m(t_vec3f v, t_matrix m);
t_matrix				transpose_matrix3(t_matrix m);
double					det3(t_matrix m);
t_matrix				inv_mx3(t_matrix m);
t_vec3f					sub(t_vec3f u, t_vec3f v);
t_vec3f					add(t_vec3f u, t_vec3f v);
t_vec3f					mul(t_vec3f u, double v);
double					dot(t_vec3f u, t_vec3f v);
t_vec3f					cross(t_vec3f u, t_vec3f v);
double					len(t_vec3f v);
t_vec3f					normalize(t_vec3f v);

#endif
