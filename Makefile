all:
	gcc -L./mlx -lmlx -framework OpenGL -framework AppKit game.c
	./a.out