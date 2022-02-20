NAME = cub3D

SRCS =	./source/ft_atoi.c ./source/ft_bzero.c ./source/ft_isdigit.c \
./source/ft_strlcpy.c ./source/get_next_line.c \
./source/get_next_line_utils.c screenshot.c main.c \
parser.c calculate_before_draw3d.c check_params.c map_checker.c \
player.c resolution.c draw_3d.c mlx.c draw_sprites.c \
textures.c free_and_exit.c move.c work_with_tmp_mass.c get_sprite.c \
parse_color.c draw_2d.c

LIBNAME = cub3d.a

FLAGS = -Wall -Wextra -Werror -MMD 

MLXLIB = minilibx_mms_20200219

MLX = libmlx.dylib

DEP = $(SRCS:.c=.d)

MLXFLAGS = -framework OpenGL -framework AppKit

OBJECTS = $(patsubst %.c,%.o,$(SRCS))

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJECTS)
	make -C $(MLXLIB)
	mv minilibx_mms_20200219/$(MLX) ./
	gcc -L. -lmlx $(MLXFLAGS) $(OBJECTS) -o $(NAME) 

%.o:%.c
	gcc $(FLAGS) -I cub.h -I $(MLXLIB) -c $< -o $@

norme:
			@norminette  $(SRCS) cube.h 

clean:
		rm -f $(OBJECTS)
		rm -f $(MLX)
		rm -f $(DEP)

fclean: clean
	rm -rf $(NAME)
	/bin/rm -f $(LIBNAME)
	/bin/rm -f screenshot.bmp

re: fclean all