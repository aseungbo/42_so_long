// 헤더 추가
#include "so_long.h"

int				main_loop(t_game *game)
{
	draw_textures(game);
	return (0);
}

int				main(int argc, char **argv)
{
	t_game		game;

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
