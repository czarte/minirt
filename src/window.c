/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/30 19:26:57 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_mlx_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		perror("Error mlx_init()\n");
		return (-1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!data->win_ptr)
	{
		perror("Error mlx_new_window()\n");
		return (-1);
	}
	return (0);
}

void    to_left(void *shp) {
    t_shapes	*shape;

    shape = (t_shapes *)shp;
    shape->cords.x += 1;
}

void    to_right(void *shp) {
    t_shapes	*shape;

    shape = (t_shapes *)shp;
    shape->cords.x -= 1;
}

void    to_top(void *shp) {
    t_shapes	*shape;

    shape = (t_shapes *)shp;
    shape->cords.y -= 1;
}

void    to_bottom(void *shp) {
    t_shapes	*shape;

    shape = (t_shapes *)shp;
    shape->cords.y += 1;
}

void    to_forw(void *shp) {
    t_shapes	*shape;

    shape = (t_shapes *)shp;
    shape->cords.z += 1;
}

void    to_back(void *shp) {
    t_shapes	*shape;

    shape = (t_shapes *)shp;
    shape->cords.z -= 1;
}

int	key_exit(int key, void *params)
{
	t_data	*data;

	data = (t_data *) params;
	printf("Keys in miniRT : %d\n", key);
	if (key == KEY_ESC || key == 17 || key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free_data(data);
		exit(0);
	}
    if (key == KEY_A || key == KEY_LEFT) { //left
        ft_lstiter(data->shapes, &to_left);
        data->scene->cam.cords.x -= 1;
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        cast_rays(data);
    }
    if (key == KEY_D || key == KEY_RIGHT) { //right
        ft_lstiter(data->shapes, &to_right);
        data->scene->cam.cords.x += 1;
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        cast_rays(data);
    }
    if (key == KEY_DOWN) { //bottom
        ft_lstiter(data->shapes, &to_bottom);
        data->scene->cam.cords.y -= 1;
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        cast_rays(data);
    }
    if (key == KEY_UP) {  //top
        ft_lstiter(data->shapes, &to_top);
        data->scene->cam.cords.y += 1;
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        cast_rays(data);
    }
    if (key == KEY_W || key == KEY_FORWARD) {  //forward
		data->scene->cam.cords.z += 1;
		// ft_lstiter(data->shapes, &to_forw);
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        cast_rays(data);
    }
    if (key == KEY_S || key == KEY_BACKWARD) {  //backward
		data->scene->cam.cords.z -= 1;
        //ft_lstiter(data->shapes, &to_back);
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        cast_rays(data);
    }
	return (0);
}

int	check_exit_button(int button, int x, int y, void *params)
{
	t_data	*data;

	data = (t_data *) params;
	(void) x;
	(void) y;
	if (button == 32)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		//mlx_destroy_display(data->mlx_ptr);
		free_data(data);
		exit(0);
	}
	return (0);
}

int	check_mouse_button(int button, int x, int y, void *params)
{
	t_data	*data;

	data = (t_data *) params;
	(void) x;
	(void) y;
	if (button == 17)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free_data(data);
		exit(0);
	}
	return (0);
}
