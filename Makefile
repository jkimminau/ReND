NAME = rnd

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADER_DIR =	.	\

OBJ_D = object_files/

SRC_C =	rnd.c		\
		draw.c		\
		connect.c	\
		data.c		\
		event.c		\
		init.c		\
		view.c		\


OBJ = $(SRC_C:.c=.o)

SRC = $(addprefix src/, $(SRC_C))

LIBFT =		libft/libft.a
LIBFTH =	libft/libft.h
LIBFTLNK =	-L libft/ -l ft

MLX =		minilibx/libmlx.a
MLXH =		minilibx/mlx.h
MLXLNK =	-L minilibx/ -l mlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBFT):
	make -C libft/

$(MLX):
	make -C minilibx/

$(OBJ): $(SRC)
	gcc $(CFLAGS) -c $(SRC) -I .

$(NAME): $(LIBFT) $(OBJ) $(MLX)
	gcc $(OBJ) -o $(NAME) $(LIBFTLNK) $(MLXLNK)
	mkdir -p $(OBJ_D)
	mv $(OBJ) $(OBJ_D)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	make fclean -C libft/
	make clean -C minilibx/
	/bin/rm -f $(NAME)

re: fclean all
