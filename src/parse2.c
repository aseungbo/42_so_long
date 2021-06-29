#include "so_long.h"

char	*map_read_and_init(t_game *game, int fd)
{
	char	*line;
	int		row;
	int		col;
	char	*string;

	row = 1;
	string = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		string = ft_strjoin(string, line);
		row++;
	}
	string = ft_strjoin(string, line);
	col = ft_strlen(line);
	game->map_info.row = row;
	game->map_info.col = col;
	game->win_info.width = col * 64;
	game->win_info.height = row * 64;
	game->play_info.coin_num = 0;
	game->play_info.exit_num = 0;
	game->play_info.pos_x = -1;
	game->play_info.pos_y = -1;
	return (string);
}

int		malloc_map_info(t_game *game, char *map_string)
{
	int i;
	int j;

	game->map_info.map = (char **)malloc(sizeof(char *) * game->map_info.row);
	if (!(game->map_info.map))
		return (0);
	i = -1;
	while (++i < game->map_info.row)
	{
		game->map_info.map[i] = malloc(sizeof(char) * (game->map_info.col + 1));
		if (!(game->map_info.map[i]))
			return (0);
	}
	i = 0;
	while (i < game->map_info.row)
	{
		j = 0;
		while (j < game->map_info.col)
		{
			game->map_info.map[i][j] = map_string[i * game->map_info.col + j];
			j++;
		}
		i++;
	}
	return (1);
}

int		map_elem_counting(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->map_info.row)
	{
		j = 0;
		while (j < game->map_info.col)
		{
			if (game->map_info.map[i][j] == 'P')
			{
				if (game->play_info.pos_x > 0 && game->play_info.pos_y > 0)
					return (1);
				game->play_info.pos_x = j;
				game->play_info.pos_y = i;
			}
			else if (game->map_info.map[i][j] == 'C')
				game->play_info.coin_num++;
			else if (game->map_info.map[i][j] == 'E')
				game->play_info.exit_num++;
			j++;
		}
		i++;
	}
	return (0);
}

int		all_boundary_is_not_wall(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map_info.col)
	{
		if (game->map_info.map[0][i] != '1')
			return (0);
		if (game->map_info.map[game->map_info.row - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map_info.row)
	{
		if (game->map_info.map[i][0] != '1')
			return (0);
		if (game->map_info.map[i][game->map_info.col - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int		some_elem_is_not_missing(t_game *game)
{
	if (game->play_info.exit_num < 1)
		return (0);
	if (game->play_info.coin_num < 1)
		return (0);
	if (game->play_info.pos_x < 0 || game->play_info.pos_y < 0)
		return (0);
	return (1);
}
