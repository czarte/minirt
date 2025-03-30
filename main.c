/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/15 15:16:22 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minirt.h"

void place_images(s_data *data)
{
	t_list **temp = data->shapes;
	while (*temp != NULL) {
		s_shapes *shp = (s_shapes *) (*temp)->content;
		if (ft_strncmp(shp->identifier, "sp", 2) == 0) {
			printf("diameter %f\n", shp->diameter);
			printf("height %f\n", shp->height);
			for (int i = 0; i < (int) shp->diameter; i++) {
				for (int j = 0; j < (int) shp->diameter; j++) {
					mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 999);
				}
			}
		}
		// shp->img = mlx_new_image(data->mlx_ptr, (int) shp->diameter + 1, (int) shp->height + 1);

		// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, shp->img, (int) shp->cords.x, (int) shp->cords.y);
		// printf("--------\n%s \ncoords:\t%.1f %.1f %.1f; \naxis:\t%.1f %.1f %.1f;\nd:\t\t%.2f;\th: %.2f;\nrgb:\t[%d, %d, %d] \n",
		// 	shp->identifier, shp->cords.x, shp->cords.y, shp->cords.z,
		// 	shp->axis.x, shp->axis.y, shp->axis.z, shp->diameter, shp->height,
		// 	shp->rgb.r, shp->rgb.g, shp->rgb.b);
		temp = &(*temp)->next;
	}
}

int	main(int argc, char *argv[])
{
	s_data	*data;

	data = malloc(sizeof(s_data));
	if (data == NULL)
		return (-1);
	if (init_program(data, argc, argv) == -1)
		exit(-1);
	if (init_mlx_window(data) == -1)
		exit(-1);
    place_images(data);
	mlx_key_hook(data->win_ptr, &key_exit, (void *)data);
	mlx_mouse_hook(data->win_ptr, &check_mouse_button, (void *)data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_data(data);
	exit(0);
	return (0);
}
