// 헤더 추가
#include "so_long.h"

void			play_condition(t_game *game)
{
	static int	cnt;

	if (game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] == 'C')
	{
		game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] = '0';
		cnt++;
		printf("the current number of coin: %d :)\n", cnt);
	}
	if (cnt == game->play_info.coin_num &&
		game->map_info.map[game->play_info.pos_y][game->play_info.pos_x] == 'E')
		exit(0);
}

void			move_cnt(int key_code, t_game *game)
{
	static int	cnt;

	if (key_code == KEY_W)
		game->play_info.pos_y--;
	else if (key_code == KEY_S)
		game->play_info.pos_y++;
	else if (key_code == KEY_A)
		game->play_info.pos_x--;
	else if (key_code == KEY_D)
		game->play_info.pos_x++;
	cnt++;
	printf("the current number of movements: %d\n", cnt);
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
