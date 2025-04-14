/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/04/04 17:25:35 by voparkan         ###   ########.fr       */
=======
/*   Updated: 2025/04/07 13:54:48 by aevstign         ###   ########.fr       */
>>>>>>> Stashed changes
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
			for (int i = 0; i < (int) shp->diameter; i++) {
				for (int j = 0; j < (int) shp->diameter; j++) {
					if (in_sphere(i, j, shp))
						mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int) shp->cords.x + i, (int) shp->cords.y + j, color);
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

// For now it causes memory leak
void	create_viewport(int image_width,
	double aspect_ratio, t_camera *camera)
{
	int		image_height;
	t_vec	temp;

	camera->focal_length = 1.0;
	image_height = (int)(image_width / aspect_ratio);
	if (image_height < 1)
		image_height = 1;
	camera->viewport_height = 2.0;
	camera->viewport_width = (camera->viewport_height
			* (double (image_width / image_height)));
	camera->viewport_u = new_vec(camera->viewport_width, 0, 0);
	camera->viewport_v = new_vec(0, -camera->viewport_height, 0);
	temp = substract(divide_by_scalar(camera->viewport_u, 2),
			divide_by_scalar(camera->viewport_v, 2));
	camera->left_upper_corner = substract(substract(camera->position,
				vec3(0, 0, camera->focal_length)), temp);
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
