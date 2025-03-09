
#include "include/minirt.h"

int	key_exit(int key, void *params)
{
	s_data	*data = (s_data *)params;
	printf("Keys in miniRT : %d\n", key);
	if (key==65307 || key==65317) {
		mlx_destroy_window(data->mlx_ptr,data->win_ptr);
		exit(0);
    }
	return (0);
}

int	check_exit_keys(void *params)
{
  	s_data	*data = (s_data *)params;
    printf("Keys in check_exit_keys : %x\n", keys);
	if (keys==27)
		mlx_destroy_window(data->mlx_ptr,data->win_ptr);
    return (0);
}

int main(void)
{
    s_data *data;
	data = malloc(sizeof(s_data));
    data->mlx_ptr = mlx_init();
    if (!(data->mlx_ptr))
    	printf("Error mlx_init()\n");
    else
    	printf("Hello, World!\n");
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
//	mlx_key_hook(data->mlx_ptr, &key_win1, (void *)data);
    mlx_key_hook(data->win_ptr, &key_exit, (void *)data);
//    mlx_key_hook(data->mlx_ptr, &check_exit_keys, (void *)data);
	mlx_loop_hook(data->mlx_ptr, &check_exit_keys, (void *)data);
	mlx_loop(data->mlx_ptr);
	return 0;
}
