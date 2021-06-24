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

# define TILE_SIZE 64
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE
# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

typedef struct	s_tile_info
{
	int		width;
	int 	height;
}				t_tile_info;

typedef struct	s_tile
{
	void	*floor;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collectible;
}				t_tile;

typedef struct	s_win_info
{
	void		*mlx;
	void		*win;
}				t_win_info;

typedef struct	s_play_info
{
	int     	rot_x;
    int     	rot_y;
	int		map[ROWS][COLS];
}				t_play_info;

typedef struct	s_game
{
	t_win_info  win_info;
	t_tile		tiles;
	t_tile_info	tile_info;
    t_play_info play_info;
}				t_game;

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
            // free space
			mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.floor,
					j * game->tile_info.width, i * game->tile_info.height);
            // wall, Add img
			if (game->play_info.map[i][j] == 1)
            {
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.wall,
					j * game->tile_info.width, i * game->tile_info.height);
                // draw_img(game, j, i);
            }
            // C, instead of img
            else if (game->play_info.map[i][j] == 'C')
			{
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.collectible,
					j * game->tile_info.width, i * game->tile_info.height);
            }
			// E, instead of img
            else if (game->play_info.map[i][j] == 'E')
			{
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.exit,
					j * game->tile_info.width, i * game->tile_info.height);
            }
			// player, instead of img
            else if (game->play_info.rot_x == i && game->play_info.rot_y == j)
            {
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.player,
					j * game->tile_info.width, i * game->tile_info.height);
			}
			j++;
		}
		i++;
	}
}

int		deal_key(int key_code, t_game *game)
{
    static int cnt;

	if (key_code == KEY_W) // Action when W key pressed
    {
        if (game->play_info.map[game->play_info.rot_x - 1][game->play_info.rot_y] != 1)
        {
		    game->play_info.rot_x--;
            cnt++;
        }
    }
    else if (key_code == KEY_S) // Action when S key pressed
	{
        if (game->play_info.map[game->play_info.rot_x + 1][game->play_info.rot_y] != 1)
		{
            game->play_info.rot_x++;
            cnt++;
        }
    }
    else if (key_code == KEY_A) // Action when A key pressed
	{
        if (game->play_info.map[game->play_info.rot_x][game->play_info.rot_y - 1] != 1)
        {
            game->play_info.rot_y--;
            cnt++
        }
    }
    else if (key_code == KEY_D) // Action when D key pressed
	{
        if (game->play_info.map[game->play_info.rot_x][game->play_info.rot_y + 1] != 1)
		{
            game->play_info.rot_y++;
            cnt++;
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
	{1, 0, 'C', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 'P', 0, 0, 0, 0, 0, 0, 1, 'E', 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 'C', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
    game->play_info.rot_x = 4;
    game->play_info.rot_y = 3;
	memcpy(game->play_info.map, map, sizeof(int) * ROWS * COLS);
}

void	window_init(t_game *game)
{
	game->win_info.mlx = mlx_init();
	game->win_info.win = mlx_new_window(game->win_info.mlx, WIDTH, HEIGHT, "./so_long");
}

void	tile_init(t_game *game)
{
	game->tiles.floor = mlx_xpm_file_to_image(game->win_info.mlx, "./textures/floor.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.wall = mlx_xpm_file_to_image(game->win_info.mlx, "./textures/wall.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.collectible = mlx_xpm_file_to_image(game->win_info.mlx, "./textures/collectible.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.exit = mlx_xpm_file_to_image(game->win_info.mlx, "./textures/exit.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.player = mlx_xpm_file_to_image(game->win_info.mlx, "./textures/player.xpm", &game->tile_info.width, &game->tile_info.height);
}

void    play_condition(t_game *game)
{
    static int cnt;

    if (game->play_info.map[game->play_info.rot_x][game->play_info.rot_y] == 'C')
    {
        game->play_info.map[game->play_info.rot_x][game->play_info.rot_y] = 0;
        cnt++;
        printf("획득한 C의 개수: %d \n", cnt);
    }
    else if (cnt == 2 && game->play_info.map[game->play_info.rot_x][game->play_info.rot_y] == 'E')
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
	tile_init(&game);
	mlx_hook(game.win_info.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win_info.win, X_EVENT_KEY_EXIT, 0, &process_close, &game);
	mlx_loop_hook(game.win_info.mlx, &main_loop, &game);
	mlx_loop(game.win_info.mlx);
}