/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/15 15:23:05 by voparkan         ###   ########.fr       */
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

int	key_exit(int key, void *params)
{
	t_data	*data;

	data = (t_data *) params;
	printf("Keys in miniRT : %d\n", key);
	if (key == 65307 || key == 17)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		//mlx_destroy_display(data->mlx_ptr);
		free_data(data);
		exit(0);
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
//		mlx_destroy_display(data->mlx_ptr);
		free_data(data);
		exit(0);
	}
	return (0);
}
