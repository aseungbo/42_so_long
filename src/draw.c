#include "so_long.h"

void	draw_textures(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map_info.row)
	{
		j = -1;
		while (++j < game->map_info.col)
		{
			mlx_put_image_to_window(game->win_info.mlx, game->win_info.win,
	game->tiles.floor, j * game->tile_info.width, i * game->tile_info.height);
			if (game->map_info.map[i][j] == '1')
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win,
game->tiles.wall, j * game->tile_info.width, i * game->tile_info.height);
			else if (game->map_info.map[i][j] == 'C')
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win,
game->tiles.collectible, j * game->tile_info.width, i * game->tile_info.height);
			else if (game->map_info.map[i][j] == 'E')
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win,
game->tiles.exit, j * game->tile_info.width, i * game->tile_info.height);
			else if (game->play_info.pos_x == j && game->play_info.pos_y == i)
				mlx_put_image_to_window(game->win_info.mlx, game->win_info.win,
game->tiles.player, j * game->tile_info.width, i * game->tile_info.height);
		}
	}
}
