TARGET  = so_long

CC		= gcc -Wall -Wextra -Werror

MLX 	= -L../mlx -lmlx -framework OpenGL -framework AppKit

RM		= rm -rf

SRC		= 	so_long.c \
			get_next_line.c \
			get_next_line_utils.c \
			utils_1.c 

OBJ = $(SRC:.c=.o)

all : $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(MLX) $(OBJ) -I so_long.h -o $(TARGET)

clean :
		$(RM) *.o

fclean : clean
		$(RM) $(TARGET)

re : fclean clean all

.PHONY : all fclean clean re