#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17 //exit key code

//Mac key code example
//All the key code example other than below is described on the site linked in READEME.md
#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

//Since key_press() can recieve only one argument, all the argument shold be gathered in one structure
//x,y and str are meaningless variables.
typedef struct s_param{
	int		x;
	int		y;
	// char	str[3];
}				t_param;

//Only param->x will be used. 
void			param_init(t_param *param)
{
	param->x = 0;
	param->y = 0;
	// param->str[0] = 'a';
	// param->str[1] = 'b';
	// param->str[2] = '\0';
}

int				key_press(int keycode, t_param *param)
{
	static int a = 0;

	if (keycode == KEY_W)//Action when W key pressed
    {
		param->y++;
        printf("y: %d\n", param->y);
    }
    else if (keycode == KEY_S) //Action when S key pressed
	{
		param->y--;
        printf("y: %d\n", param->y);
    }
    else if (keycode == KEY_A) //Action when A key pressed
	{
		param->x++;
        printf("x: %d\n", param->x);
    }
    else if (keycode == KEY_D) //Action when D key pressed
	{
		param->x--;
        printf("x: %d\n", param->x);
    }
	else if (keycode == KEY_ESC) //Quit the program when ESC key pressed
		exit(0);
	return (0);
}

int main()
{
    void	*mlx_ptr;
    void 	*win_ptr;
    int		width;
    int		height;
    t_param param;
    
    width = 400;
    height = 400;
    param_init(&param);
    mlx_ptr = mlx_init();	//mlx 할당 실패할 경우 NULL반환
    win_ptr = mlx_new_window(mlx_ptr, width, height, "./so_long"); 
    				// 할당된 mlx에 너비. 높이를 갖는 윈도우 창 생성.
    mlx_hook(win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &param);
    mlx_loop(mlx_ptr);
}
