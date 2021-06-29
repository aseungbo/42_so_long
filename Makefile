TARGET  = so_long

CC		= gcc -Wall -Wextra -Werror

MLX_PATH = ./mlx/
MLX	     = $(MLX_PATH)libmlx.a
MLX		+= -lm -Imlx -framework OpenGL -framework AppKit
RM		= rm -rf

SRC		= 	src/so_long.c \
			src/init.c \
			src/parse.c \
			src/parse2.c \
			src/draw.c \
			src/deal_key.c \
			src/get_next_line.c \
			src/get_next_line_utils.c \
			src/utils_1.c \
			src/utils_2.c \
			src/utils_3.c \

OBJ = $(SRC:.c=.o)

all : $(TARGET)

$(TARGET): $(OBJ)
	make -C ./mlx
	$(CC) $(MLX) $(OBJ) -I so_long.h -o $(TARGET)

clean :
		make clean -C ./mlx
		$(RM) ./src/*.o

fclean : clean
		$(RM) $(TARGET)

re : fclean clean all

.PHONY : all fclean clean re
