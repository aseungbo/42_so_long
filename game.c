#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./mlx/mlx.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code = Red cross key

#define KEY_ESC			53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define TILE_SIZE 32
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE
# define COUNT ROWS * COLS
# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

typedef struct	s_img
{
	void	*img;
	int		width;
	int 	height;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	tiles;
    int     rot_x;
    int     rot_y;

	int		map[ROWS][COLS];
}				t_game;

// void	draw_rectangle(t_game *game, int x, int y, int color)
// {
// 	int i;
// 	int j;
//     int	img_width;
// 	int img_height;

// 	x *= TILE_SIZE;
// 	y *= TILE_SIZE;
// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			game->img.data[(y + i) * WIDTH + x + j] = color;
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_rectangles(t_game *game)
// {
// 	int		i;
// 	int		j;
//     int		img_width;
// 	int 	img_height;

// 	i = 0;
// 	while (i < ROWS)
// 	{
// 		j = 0;
// 		while (j < COLS)
// 		{
//             // free space
//             draw_rectangle(game, j, i, 0x000000);

//             // wall, Add img
// 			if (game->map[i][j] == 1)
//             {
// 				draw_rectangle(game, j, i, 0xFFFFFF);
//                 // draw_img(game, j, i);
//             }
//             // C, instead of img
//             else if (game->map[i][j] == 69)
//                 draw_rectangle(game, j, i, 0xFFFF00);
//             // E, instead of img
//             else if (game->map[i][j] == 67)
//                 draw_rectangle(game, j, i, 0x0000FF);
//             // player, instead of img
//             else if (game->rot_x == i && game->rot_y == j)
//                 draw_rectangle(game, j, i, 0x7FFF00);
//             // Bonus: enemy patrols, instead of img
//             else if (game->map[i][j] == 75)
//                 draw_rectangle(game, j, i, 0xFF0000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_textures(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
            // // free space
			game->tiles.img = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm", &game->tiles.width, &game->tiles.height);
			mlx_put_image_to_window(game->mlx, game->win, game->tiles.img,
					j * game->tiles.width, i * game->tiles.height);
            // // wall, Add img
			if (game->map[i][j] == 1)
            {
				game->tiles.img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &game->tiles.width, &game->tiles.height);
				mlx_put_image_to_window(game->mlx, game->win, game->tiles.img,
					j * game->tiles.width, i * game->tiles.height);
                // draw_img(game, j, i);
            }
            // // C, instead of img
            else if (game->map[i][j] == 69)
			{
                game->tiles.img = mlx_xpm_file_to_image(game->mlx, "./textures/collectible.xpm", &game->tiles.width, &game->tiles.height);
				mlx_put_image_to_window(game->mlx, game->win, game->tiles.img,
					j * game->tiles.width, i * game->tiles.height);
            }
			// // E, instead of img
            else if (game->map[i][j] == 67)
			{
				game->tiles.img = mlx_xpm_file_to_image(game->mlx, "./textures/exit.xpm", &game->tiles.width, &game->tiles.height);
				mlx_put_image_to_window(game->mlx, game->win, game->tiles.img,
					j * game->tiles.width, i * game->tiles.height);
            }
			// player, instead of img
            else if (game->rot_x == i && game->rot_y == j)
            {
				game->tiles.img = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm", &game->tiles.width, &game->tiles.height);
				mlx_put_image_to_window(game->mlx, game->win, game->tiles.img,
					j * game->tiles.width, i * game->tiles.height);
			}
            // Bonus: enemy patrols, instead of img
            else if (game->map[i][j] == 75)
			{
				game->tiles.img = mlx_xpm_file_to_image(game->mlx, "./textures/fail.xpm", &game->tiles.width, &game->tiles.height);
				mlx_put_image_to_window(game->mlx, game->win, game->tiles.img,
					j * game->tiles.width, i * game->tiles.height);
			}
			j++;
		}
		i++;
	}
}

int		deal_key(int key_code, t_game *game)
{
    static int cnt;

	if (key_code == KEY_W) //Action when W key pressed
    {
        if (game->map[game->rot_x - 1][game->rot_y] != 1)
        {
		    game->rot_x--;
            cnt++;
            // printf("y: %d\n", game->rot_y);
        }
    }
    else if (key_code == KEY_S) //Action when S key pressed
	{
        if (game->map[game->rot_x + 1][game->rot_y] != 1)
		{
            game->rot_x++;
            cnt++;
            // printf("y: %d\n", game->rot_y);
        }
    }
    else if (key_code == KEY_A) //Action when A key pressed
	{
        if (game->map[game->rot_x][game->rot_y - 1] != 1)
        {
            game->rot_y--;
            cnt++;
            // printf("x: %d\n", game->rot_x);
        }
    }
    else if (key_code == KEY_D) //Action when D key pressed
	{
        if (game->map[game->rot_x][game->rot_y + 1] != 1)
		{
            game->rot_y++;
            // cnt++;
            // printf("x: %d\n", game->rot_x);
        }
    }
	else if (key_code == KEY_ESC)
		exit(0);
    printf("the current number of movements: %d\n", cnt);
    return (0);
}

int	process_close(void)
{
	exit(0);
}

void	game_init(t_game *game)
{	
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 80, 0, 0, 0, 0, 0, 0, 1, 69, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 75, 1, 1, 1, 1, 1, 0, 1},
	{1, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
    game->rot_x = 4;
    game->rot_y = 3;
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "./so_long");
}

void    play_condition(t_game *game)
{
    static int cnt;

    if (game->map[game->rot_x][game->rot_y] == 67)
    {
        game->map[game->rot_x][game->rot_y] = 0;
        cnt++;
        printf("획득한 C의 개수: %d \n", cnt);
    }
    // Bonus : enemy patrols
    else if (game->map[game->rot_x][game->rot_y] == 75)
        exit(0);
    else if (cnt == 2 && game->map[game->rot_x][game->rot_y] == 69)
        exit(0);
}
int		main_loop(t_game *game)
{
    play_condition(game);
	draw_textures(game);
	return (0);
}

int		main(void)
{
	t_game game;

	game_init(&game);
	window_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &process_close, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}