// 헤더 추가
#include "so_long.h"

int				deal_key(int key_code, t_game *game)
{
	static int	cnt;

	if (key_code == KEY_W &&
	game->map_info.map[game->play_info.pos_y - 1][game->play_info.pos_x] != '1')
	{
		game->play_info.pos_y--;
		cnt++;
	}
	else if (key_code == KEY_S &&
	game->map_info.map[game->play_info.pos_y + 1][game->play_info.pos_x] != '1')
	{
		game->play_info.pos_y++;
		cnt++;
	}
	else if (key_code == KEY_A &&
	game->map_info.map[game->play_info.pos_y][game->play_info.pos_x - 1] != '1')
	{
		game->play_info.pos_x--;
		cnt++;
	}
	else if (key_code == KEY_D &&
	game->map_info.map[game->play_info.pos_y][game->play_info.pos_x + 1] != '1')
	{
		game->play_info.pos_x++;
		cnt++;
	}
	else if (key_code == KEY_ESC)
		exit(0);
	printf("the current number of movements: %d\n", cnt);
	return (0);
}

int				process_close(void)
{
	exit(0);
}
