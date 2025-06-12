/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/21 19:59:13 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_mlx_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
        free_data(data);
		perror("Error mlx_init()\n");
		return (-1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!data->win_ptr)
	{
        free_data(data);
		perror("Error mlx_new_window()\n");
		return (-1);
	}
	return (0);
}

void	resolve_light_move(t_data *data, int key, bool *cast)
{
	if (key == L_KEY_A_L || key == L_KEY_D_R || key == L_KEY_S_B
		|| key == L_KEY_W_U)
	{
		*cast = true;
		data->frame++;
	}
	if (key == L_KEY_A_L)
		data->scene->lght.cords.x -= 1;
	if (key == L_KEY_D_R)
		data->scene->lght.cords.x += 1;
	if (key == L_KEY_S_B)
		data->scene->lght.cords.y -= 1;
	if (key == L_KEY_W_U)
		data->scene->lght.cords.y += 1;
}

int	key_mapping(int key, void *params)
{
	bool	cast;
	t_data	*data;
	int		frame_n;

	cast = false;
	data = (t_data *) params;
	frame_n = data->frame % 2;
	if (key == KEY_ESC || key == 17 || key == 53)
		mlx_loop_end(data->mlx_ptr);
	resolve_light_move(data, key, &cast);
	if (cast)
	{
		cast_rays(data);
		mlx_destroy_image(data->mlx_ptr, data->scene_img[frame_n]->ptr);
	}
	return (0);
}
