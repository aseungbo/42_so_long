// 헤더 추가
#include "so_long.h"

char	*map_read_and_init(t_game *game, int fd)
{
	char	*line;
	int		row;
	int		col;
	char	*string;

	row = 1;
	string = "";
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

void	malloc_map_info(t_game *game, char *map_string)
{
	int i;
	int start = 0;

	i = 0;
	game->map_info.map = (char **)malloc(sizeof(char *) * game->map_info.row);

	while (i < game->map_info.row)
	{
		game->map_info.map[i] = malloc(sizeof(char) * (game->map_info.col + 1));
		i++;
	}

	i = 0;
	while (i < game->map_info.row)
	{
		game->map_info.map[i] = ft_substr(map_string, start, game->map_info.col);
		start += game->map_info.col;
		i++;
	}
}

void	map_elem_counting(t_game *game)
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
		if (game->map_info.map[game->map_info.col - 1][0] != '1')
			return (0);
		i++;
	}
	return (1);
}


void	free_all_thing(t_game *game)
{
	int i;

	i = 0;
	if (game->map_info.map)
	{
		while (i < game->map_info.row)
			free(game->map_info.map[i++]);
		free(game->map_info.map);
	}
}

void	print_error(t_game *game, char *e_msg)
{
	write(1, "Error\n", 7);
	if (e_msg)
		write(2, e_msg, ft_strlen(e_msg));
	free_all_thing(game);
	exit(EXIT_FAILURE);
}

int		extension_is_ber(char *file_name)
{
	int ptr;
	
	ptr = ft_strlen(file_name) - 1;
	if (file_name[ptr] != 'r')
		return (0);
	if (file_name[ptr - 1] != 'e')
		return (0);
	if (file_name[ptr - 2] != 'b')
		return (0);
	if (file_name[ptr - 3] != '.')
		return (0);
	return (1);
}

int 	map_parse(t_game *game, int fd)
{
	char *map_string;

	map_string = map_read_and_init(game, fd);

	malloc_map_info(game, map_string);

	map_elem_counting(game);

	if (!all_boundary_is_not_wall(game))
		return (0);
	if (!some_elem_is_not_missing(game))
		return (0);
	return (1);
}

void	check_arguments(t_game *game, int argc, char **argv)
{
	int		fd;

	if (argc != 2)
		print_error(game, "[ERROR]: need one argument\n");
	else if (!extension_is_ber(argv[1]))
		print_error(game, "[ERROR]: file extension is not .ber\n");
	fd = open(argv[1], O_RDONLY);
	if (!map_parse(game, fd))
		print_error(game, "[ERROR]: invalid map\n");
}
