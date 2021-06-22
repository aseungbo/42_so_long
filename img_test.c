#include <stdio.h>
#include "./mlx/mlx.h"

typedef struct	s_img
{
	void	*img;
    void    *img_file;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_game;


int main()
{
		int		img_width;
		int 	img_height;
        t_game  game;

		game.mlx = mlx_init();
		game.win = mlx_new_window(game.mlx, 500, 500, "my_mlx");
		game.img.img_file = mlx_xpm_file_to_image(game.mlx, "./wall_e.xpm", &img_width, &img_height);
		mlx_put_image_to_window(game.mlx, game.win, game.img.img_file, 0, 0);
		mlx_loop(game.mlx);
		return (0);
}
