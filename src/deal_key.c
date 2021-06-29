#include "so_long.h"

void			play_condition(t_game *game)
{
	static int	cnt;

	if (game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] == 'C')
	{
		game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] = '0';
		cnt++;
	}
	if (cnt == game->play_info.coin_num &&
		game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] == 'E')
	{
		free_all_thing(game);
		mlx_destroy_window(game->win_info.mlx, game->win_info.win);
		mlx_destroy_image(game->win_info.mlx, game->tiles.floor);
		mlx_destroy_image(game->win_info.mlx, game->tiles.wall);
		mlx_destroy_image(game->win_info.mlx, game->tiles.player);
		mlx_destroy_image(game->win_info.mlx, game->tiles.exit);
		mlx_destroy_image(game->win_info.mlx, game->tiles.collectible);
		exit(0);
	}
}

void			move_cnt(int key_code, t_game *game)
{
	static int	cnt;
	char		*dum;

	if (key_code == KEY_W)
		game->play_info.pos_y--;
	else if (key_code == KEY_S)
		game->play_info.pos_y++;
	else if (key_code == KEY_A)
		game->play_info.pos_x--;
	else if (key_code == KEY_D)
		game->play_info.pos_x++;
	cnt++;
	if (!(dum = ft_itoa(cnt)))
		exit(0);
	ft_putstr_fd("움직인 횟수: ", 1);
	ft_putstr_fd(dum, 1);
	ft_putchar_fd('\n', 1);
	free(dum);
}

int				deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_W &&
	game->map_info.map[game->play_info.pos_y - 1][game->play_info.pos_x] != '1')
		move_cnt(key_code, game);
	else if (key_code == KEY_S &&
	game->map_info.map[game->play_info.pos_y + 1][game->play_info.pos_x] != '1')
		move_cnt(key_code, game);
	else if (key_code == KEY_A &&
	game->map_info.map[game->play_info.pos_y][game->play_info.pos_x - 1] != '1')
		move_cnt(key_code, game);
	else if (key_code == KEY_D &&
	game->map_info.map[game->play_info.pos_y][game->play_info.pos_x + 1] != '1')
		move_cnt(key_code, game);
	else if (key_code == KEY_ESC)
		exit(0);
	play_condition(game);
	return (0);
}

int				process_close(void)
{
	exit(0);
}
