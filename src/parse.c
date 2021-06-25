// 헤더 추가
#include "so_long.h"

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
