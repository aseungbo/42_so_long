// 헤더 추가
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define OPEN_MAX 256
# define BUFFER_SIZE 256
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC			53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define TILE_SIZE 64

typedef struct	s_tile_info
{
	int			width;
	int			height;
}				t_tile_info;

typedef struct	s_tile
{
	void		*floor;
	void		*wall;
	void		*player;
	void		*exit;
	void		*collectible;

}				t_tile;

typedef struct	s_win_info
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
}				t_win_info;

typedef struct	s_play_info
{
	int			pos_x;
	int			pos_y;
	int			coin_num;
}				t_play_info;

typedef struct	s_map_info
{
	int			row;
	int			col;
	char		**map;
}				t_map_info;

typedef struct	s_game
{
	t_win_info	win_info;
	t_tile		tiles;
	t_tile_info	tile_info;
	t_play_info	play_info;
	t_map_info	map_info;
}				t_game;

int				get_next_line(int fd, char **line);
size_t			ft_gnl_strlen(const char *s);
void			*ft_gnl_memcpy(void *dest, const void *src, size_t n);
char			*ft_gnl_strjoin(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			tile_init(t_game *game);
void			window_init(t_game *game);
int				map_parse(t_game *game, int fd);
void			check_arguments(t_game *game, int argc, char **argv);
void			draw_textures(t_game *game);
int				process_close(void);
int				deal_key(int key_code, t_game *game);
void			move_cnt(int key_code, t_game *game);
void			play_condition(t_game *game);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
#endif
