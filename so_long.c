#include "so_long.h"

void	draw_textures(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map_info.row)
	{
		j = 0;
		while (j < game->map_info.col)
		{
			mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.floor,
					j* game->tile_info.width, i * game->tile_info.height);
			if (game->map_info.map[i][j] == '1')
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.wall,
					j * game->tile_info.width, i * game->tile_info.height);
            else if (game->map_info.map[i][j] == 'C')
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.collectible,
					j * game->tile_info.width, i * game->tile_info.height);
            else if (game->map_info.map[i][j] == 'E')
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.exit,
					j * game->tile_info.width, i * game->tile_info.height);
            else if (game->play_info.pos_x == j && game->play_info.pos_y == i)
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win, game->tiles.player,
					j * game->tile_info.width, i * game->tile_info.height);
			j++;
		}
		i++;
	}
}

int		deal_key(int key_code, t_game *game)
{
    static int cnt;

	if (key_code == KEY_W)
    {
        if (game->map_info.map[game->play_info.pos_y - 1][game->play_info.pos_x] != '1')
        {
		    game->play_info.pos_y--;
            cnt++;
        }
    }
    else if (key_code == KEY_S)
	{
        if (game->map_info.map[game->play_info.pos_y + 1][game->play_info.pos_x] != '1')
		{
            game->play_info.pos_y++;
            cnt++;
        }
    }
    else if (key_code == KEY_A)
	{
        if (game->map_info.map[game->play_info.pos_y][game->play_info.pos_x - 1] != '1')
        {
            game->play_info.pos_x--;
            cnt++;
        }
    }
    else if (key_code == KEY_D)
	{
        if (game->map_info.map[game->play_info.pos_y][game->play_info.pos_x + 1] != '1')
		{
            game->play_info.pos_x++;
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

void	window_init(t_game *game)
{
	game->win_info.mlx = mlx_init();
	game->win_info.win = mlx_new_window(game->win_info.mlx, game->win_info.width, game->win_info.height, "./so_long");
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

    if (game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] == 'C')
    {
        game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] = '0';
        cnt++;
        printf("the current number of coin: %d :)\n", cnt);
    }
    if (cnt == game->play_info.coin_num && game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] == 'E')
        exit(0);
}

int		main_loop(t_game *game)
{
    play_condition(game);
	draw_textures(game);
	return (0);
}

int 	map_parse(t_game *game, int fd)
{
	char	*line;
	int		row;
	int		col;
	char	*string;

	row = 1;
	string = "";
	while (get_next_line(fd, &line))
	{
		// printf("%s\n", line);
		string = ft_strjoin(string, line);
		row++;
	}
	// printf("%s\n", line);
	string = ft_strjoin(string, line);
	col = ft_strlen(line);
	// printf("행의 개수: %d\n", row);
	// printf("열의 개수: %d\n", col);
	// printf("합쳐진 문자: %s\n", string);

	game->map_info.row = row;
	game->map_info.col = col;
	game->win_info.width = col * 64;
	game->win_info.height = row * 64;
	game->map_info.map = (char **)malloc(sizeof(char *) * row);
	game->play_info.coin_num = 0;

	for (int i = 0; i < row; i++)
	{
		game->map_info.map[i] = malloc(sizeof(char) * (col + 1));
	}

	int i = 0;
	int start = 0;
	while (i < row)
	{
		game->map_info.map[i] = ft_substr(string, start, col);
		start += col;
		i++;
	}

	// for (int k = 0; k < row; k++)
	// {
	// 	printf("%d번째 줄: %s\n", k + 1, game->map_info.map[k]);
	// }

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (game->map_info.map[i][j] == 'P')
			{
				game->play_info.pos_x = j;
				game->play_info.pos_y = i;
			}
			else if (game->map_info.map[i][j] == 'C')
				game->play_info.coin_num++;
		}
	}
	// printf("현재 플레이어 위치: (%d, %d)\n", game->play_info.pos_x, game->play_info.pos_y);

	return (1);
}

void	check_arguments(t_game *game, int argc, char **argv)
{
	int		fd;
	char	**tmp;
	int		tmp1;

	tmp1 = argc;
	tmp = argv;

	fd = open(argv[1], O_RDONLY);

	map_parse(game, fd);
	
}

int		main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
		exit(1);
	check_arguments(&game, argc, argv);
	window_init(&game);
	tile_init(&game);
	mlx_hook(game.win_info.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win_info.win, X_EVENT_KEY_EXIT, 0, &process_close, &game);
	mlx_loop_hook(game.win_info.mlx, &main_loop, &game);
	mlx_loop(game.win_info.mlx);
}