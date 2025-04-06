/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/06 12:47:38 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minirt.h"

bool in_sphere(int i, int j, s_shapes *shp) {
	float radius = shp->diameter / 2;
	float px = i - radius;
	float py = j - radius;
	return (px * px + py * py) <= radius * radius;
}

void make_border(s_data *data, s_shapes *shp) {
	for (int i = 0; i < (int) shp->diameter; i++) {
		for (int j = 0; j < (int) shp->diameter; j++) {
			if (i == 0 || j == 0)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int) shp->cords.x + i, (int) shp->cords.y + j, 0xFFFFFF);
			if (i == (int) shp->diameter - 1 || j == (int) shp->diameter - 1)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int) shp->cords.x + i, (int) shp->cords.y + j, 0xFFFFFF);
		}
	}
}

void place_images(s_data *data)
{
	int color;

	t_list **temp = data->shapes;
	while (*temp != NULL) {
		s_shapes *shp = (s_shapes *) (*temp)->content;
		if (ft_strncmp(shp->identifier, "sp", 2) == 0) {
			color = make_color(shp->rgb);
			printf("diameter %f\n", shp->diameter);
			printf("height %f\n", shp->height);
			printf("color %d [%d %d %d]\n", color, shp->rgb.r, shp->rgb.g, shp->rgb.b);
			//make_border(data, shp);
			//shp->img = mlx_new_image(data->mlx_ptr, (int) shp->diameter + 1, (int) shp->height + 1);
			for (int i = 0; i < (int) shp->diameter; i++) {
				for (int j = 0; j < (int) shp->diameter; j++) {
					if (in_sphere(i, j, shp))
						mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int) shp->cords.x + i, (int) shp->cords.y + j, color);
				}
			}
			///mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, shp->img, (int) shp->cords.x, (int) shp->cords.y);
		}
		if (ft_strncmp(shp->identifier, "sp", 2) == 0) {
			color = make_color(shp->rgb);

		}
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
