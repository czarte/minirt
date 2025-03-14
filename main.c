
#include "include/minirt.h"

int	key_exit(int key, void *params)
{
	s_data	*data = (s_data *)params;
	printf("Keys in miniRT : %d\n", key);
	if (key==65307 || key==17) {
		mlx_destroy_window(data->mlx_ptr,data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
		exit(0);
    }
	return (0);
}

int	check_exit_button(int button,int x,int y, void *p)
{
  	s_data	*data = (s_data *)p;
    printf("Keys in check_exit_button : %d on %d %d %p %p\n", button, x, y, data->mlx_ptr, data->win_ptr);
	if (button==32){
		mlx_destroy_window(data->mlx_ptr,data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
       	exit(0);
    }
    return (0);
}

int	check_mouse_button(int button,int x,int y, void *p)
{
  	s_data	*data = (s_data *)p;
    printf("Keys in check_mouse_button : %x on %d %d %p %p\n", button, x, y, data->mlx_ptr, data->win_ptr);
	if (button==17){
		mlx_destroy_window(data->mlx_ptr,data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        exit(0);
    }
    return (0);
}

int main(void)
{
    s_data *data;
	data = malloc(sizeof(s_data));
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr) {
    	printf("Error mlx_init()\n");
    	exit(-1);
    }
    else
    	printf("Hello, World!\n");
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->win_ptr) {
		printf("Error mlx_new_window()\n");
		exit(-1);
	}
//	mlx_key_hook(data->mlx_ptr, &key_win1, (void *)data);
    mlx_key_hook(data->win_ptr, &key_exit, (void *)data);
//    mlx_key_hook(data->mlx_ptr, &check_exit_keys, (void *)data);
	mlx_mouse_hook(data->win_ptr, &check_mouse_button, (void *)data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &mlx_loop_end, data->mlx_ptr);
	//mlx_hook(data->win_ptr, 17, 1, &check_exit_button, (void *)data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr,data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	return 0;
}
