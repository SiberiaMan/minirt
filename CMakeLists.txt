cmake_minimum_required(VERSION 3.17)
project(minirt C)

set(CMAKE_C_STANDARD 99)

add_executable(minirt main.c mlx/font.c mlx/mlx.h mlx/mlx_png.c mlx/mlx_rgb.c mlx/mlx_string_put.c mlx/mlx_xpm.c minirt.h)