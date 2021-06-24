#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> // only for testing
#include <fcntl.h>
// #include <math.h>
#include <string.h> // only for testing
#include "./mlx/mlx.h"

// gnl - macro
# define OPEN_MAX 256
# define BUFFER_SIZE 256

// so_long
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code = Red cross key

#define KEY_ESC			53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define TILE_SIZE 64
// # define ROWS 11
// # define COLS 15
// # define WIDTH COLS * TILE_SIZE
// # define HEIGHT ROWS * TILE_SIZE

typedef struct	s_tile_info
{
	int		width;				// 타일의 너비 (64)
	int 	height;				// 타일의 높이 (64)
	
}				t_tile_info;

typedef struct	s_tile
{
	void	*floor;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collectible;

}				t_tile;

typedef struct	s_win_info
{
	void		*mlx;
	void		*win;
    int         width;          // 창의 너비 = (col * 64)
    int         height;         // 창의 높이 = (row * 64)

}				t_win_info;

typedef struct	s_play_info
{
	int     	pos_x;          // 플레이어 x 좌표
    int     	pos_y;          // 플레이어 y 좌표
	// int			map[ROWS][COLS];
	int			coin_num;
}				t_play_info;

typedef struct s_map_info
{
    int         row;			// 맵의 총 행의 개수
    int         col;			// 맵의 총 열의 개수
	
    char         **map;			// 맵정보

}				t_map_info;

typedef struct		s_game
{
	t_win_info  	win_info;
	t_tile			tiles;
	t_tile_info		tile_info;
    t_play_info 	play_info;
	t_map_info		map_info;

}					t_game;


// get_next_line.c
int			get_next_line(int fd, char **line);
// get_next_line_utils.c
size_t		ft_gnl_strlen(const char *s);
void		*ft_gnl_memcpy(void *dest, const void *src, size_t n);
char		*ft_gnl_strjoin(const char *s1, const char *s2);

// utils_1.c
size_t	    ft_strlen(const char *s);
void	    *ft_memcpy(void *dest, const void *src, size_t n);
char    	*ft_strdup(const char *s);
char    	*ft_strjoin(char const *s1, char const *s2);
char    	*ft_substr(char const *s, unsigned int start, size_t len);

#endif