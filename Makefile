all:
	gcc -Wall -Wextra -Werror -L./mlx -lmlx -framework OpenGL -framework AppKit game.c
	./a.out