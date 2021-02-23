/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:31:48 by dchani            #+#    #+#             */
/*   Updated: 2021/02/09 18:31:49 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "minirt.h"

# define H_SIZE 54

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef	struct		s_vars
{
	void			*mlx;
	void			*win;
	t_data			img;
}					t_vars;

typedef struct		s_iter
{
	size_t			i;
	size_t			j;
}					t_iter;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);

#endif
