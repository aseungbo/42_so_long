#include "so_long.h"

void	window_init(t_game *game)
{
	game->win_info.mlx = mlx_init();
	game->win_info.win = mlx_new_window(game->win_info.mlx,
		game->win_info.width, game->win_info.height, "./so_long");
}

void	tile_init(t_game *game)
{
	void	*mlx;

	mlx = game->win_info.mlx;
	game->tiles.floor = mlx_xpm_file_to_image(mlx,
	"./textures/floor.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.wall = mlx_xpm_file_to_image(mlx,
	"./textures/wall.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.collectible = mlx_xpm_file_to_image(mlx,
	"./textures/coin.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.exit = mlx_xpm_file_to_image(mlx,
	"./textures/exit.xpm", &game->tile_info.width, &game->tile_info.height);
	game->tiles.player = mlx_xpm_file_to_image(mlx,
	"./textures/player.xpm", &game->tile_info.width, &game->tile_info.height);
}
