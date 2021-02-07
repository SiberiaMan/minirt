#include "mlx/mlx.h"
#include "utils/libft.h"
#include <stdio.h>

typedef struct s_data {
	void 	*img;
	char	*addr;
	int 	bits_per_pixel;
	int 	line_length;
	int 	endian;
}				t_data;

typedef struct	s_vars {
	void 	*mlx;
	void 	*win;
	t_data	img;
}				t_vars;

void 	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int 	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int				depend(int keycode, t_vars *vars)
{
	my_mlx_pixel_put(&(*vars).img, 10, 10, create_trgb(0, 0, 255, 0));
	if (keycode == 48)
	{
		int i = 0;
		for (int y = 0; y < 500; y++)
			for (int x = 0; x < 500; x++)
				my_mlx_pixel_put(&(vars->img), x, y, create_trgb(0, 0, 255, 0));
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	if(keycode == 49)
	{
		printf("no hello world\n");
		for (int y = 0; y < 500; y++)
			for (int x = 0; x < 500; x++)
				my_mlx_pixel_put(&vars->img, x, y, create_trgb(0, 0, 0, 255));
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int				main(void)
{
	t_vars		vars;

	char *s = "Hello";
	printf("%i\n", ft_strlen(s));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello World!");
	vars.img.img = mlx_new_image(vars.mlx, 500, 500);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
								   &vars.img.line_length, &vars.img.endian);
	mlx_hook(vars.win, 2, 1L << 0, depend, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
}