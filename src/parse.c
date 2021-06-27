#include "so_long.h"

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

int		map_parse(t_game *game, int fd)
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
	if (fd < 0)
		print_error(game, "[ERROR]: file isn't exist.\n");
	if (!map_parse(game, fd))
		print_error(game, "[ERROR]: invalid map\n");
}
