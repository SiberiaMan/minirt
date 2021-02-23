NAME        =	minirt
NAME_LIB	=	libmlx.dylib

SRC         =   draw/close.c\
                draw/draw.c\
                draw/export_bmp.c\
                draw/pixel.c\
                draw/vars_init.c\
                handlers/ambient_handler.c\
                handlers/camera_handler.c\
                handlers/cylinder_handler.c\
                handlers/light_handler.c\
                handlers/plane_handler.c\
                handlers/resolution_handler.c\
                handlers/sphere_handler.c\
                handlers/square_handler.c\
                handlers/triangle_handler.c\
                handlers/checks.c\
                handlers/elem_assign.c\
                handlers/parser.c\
                kernel/ray_tracing.c\
                kernel/rotate_off.c\
                kernel/rotate_on.c\
                kernel/intersections/cylinder_intersect.c\
                kernel/intersections/plane_intersect.c\
                kernel/intersections/sphere_intersect.c\
                kernel/intersections/square_intersect.c\
                kernel/intersections/triangle_intersect.c\
                kernel/raytrace_objects/cylinder_raytrace.c\
                kernel/raytrace_objects/plane_raytrace.c\
                kernel/raytrace_objects/sphere_raytrace.c\
                kernel/raytrace_objects/square_raytrace.c\
                kernel/raytrace_objects/tr_raytrace.c\
                math/matrix.c\
                math/vector_assign.c\
                math/vectors1.c\
                math/vectors2.c\
                utils/gnl/get_next_line.c\
                utils/gnl/get_next_line_utils.c\
                utils/ft_atof.c\
                utils/ft_finddict.c\
                utils/ft_lstadd_back.c\
                utils/ft_split.c\
                utils/ft_strchr.c\
                utils/ft_strlen.c\
                utils/ft_strnstr.c\
                utils/ft_tlst_add_back.c\
                utils/garbage_collector.c\
                utils/garbage_collector_brother.c\
                utils/init.c\
                main.c

includes    =	includes

OBJS	= $(SRC:.c=.o)

$(NAME): $(includes) $(SRC)
	cd mlx && make && mv $(NAME_LIB) ../. && cd ..
	gcc -Lmlx -Wall -Wextra -Werror -o $(NAME) $(NAME_LIB) $(SRC) -I $(headers)

all:	$(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf image.bmp && mv $(NAME_LIB) mlx && cd mlx && make clean && cd ../

re:		fclean all

.PHONY:	all fclean clean re