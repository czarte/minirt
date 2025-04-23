/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/24 01:03:57 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minirt.h"
#include <float.h>

void	mrt_put_pixel(t_img *img, int x, int y, int color) {
	int	offset;

	offset = (img->line_length * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->pixels)) = color;
}

bool in_sphere(int i, int j, t_shapes *shp) {
	float radius = shp->diameter / 2;
	float px = i - radius;
	float py = j - radius;
	return (px * px + py * py) <= radius * radius;
}

// void make_border(t_shapes *shp) {
// 	int color = 0xFFFFFF;
// 	for (int i = 0; i < (int) shp->diameter; i++) {
// 		for (int j = 0; j < (int) shp->diameter; j++) {
// 			if (i == 0 || j == 0)
// 				mrt_put_pixel(&shp->img, (int) shp->cords.x + i, (int) shp->cords.y + j, color);
// 			if (i == (int) shp->diameter - 1 || j == (int) shp->diameter - 1)
// 				mrt_put_pixel(&shp->img, (int) shp->cords.x + i, (int) shp->cords.y + j, color);
// 		}
// 	}
// }

// void do_sphere_img(t_data *data, int color, t_shapes *shp, t_ray *ray) {
// 	int pix_color = color;
//     float t;
//     float closest_t = FLT_MAX;
//     (void) ray;
// //	printf("diameter %f\n", shp->diameter);
// //	printf("height %f\n", shp->height);
// //	printf("color %d [%d %d %d]\n", color, shp->rgb.r, shp->rgb.g, shp->rgb.b);
// 	//make_border(shp);
// 	shp->img.mlx_ptr = data->mlx_ptr;
// 	shp->img.ptr = mlx_new_image(data->mlx_ptr, (int) shp->diameter + 1, (int) shp->diameter + 1);//(int) shp->diameter + 1, (int) shp->diameter + 1);
// 	shp->img.pixels = mlx_get_data_addr(shp->img.ptr, &shp->img.bits_per_pixel,
// 		&shp->img.line_length, &pix_color);
// 	int i = 0;
// 	while (i < (int) shp->diameter + 1) { //
// 		int j = 0;
// 		while (j < (int) shp->diameter + 1) { //
// 			if (ray_inter_sp(*ray, shp, &t)) {
//                 if (t < closest_t) {
//                     closest_t = t;
//                     mrt_put_pixel(&shp->img, i, j, color);
//                 }
//             } //ray_inter_sp(*ray, shp) && in_sphere(i, j, shp)
//             else
//                 mrt_put_pixel(&shp->img, i, j, 0xFFFFFFFF);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void place_images(t_data *data, t_ray *ray)
// {
// 	int color;

// 	t_list *temp = data->shapes;
// 	while (temp != NULL) {
// 		t_shapes *shp = (t_shapes *) temp->content;
// 		shp->img.mlx_ptr = NULL;
// 		color = make_color(shp->rgb);
// 		if (ft_strncmp(shp->identifier, "sp", 2) == 0) {
// 			do_sphere_img(data, color, shp, ray);
// 			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, shp->img.ptr,
// 				(int) shp->cords.x, (int) shp->cords.y);
// 		}
// 		if (ft_strncmp(shp->identifier, "pl", 2) == 0) {
// 		}
// 		temp = temp->next;
// 	}
// }

void	init_scene_img(t_data *data)
{
	data->scene_img.mlx_ptr = data->mlx_ptr;
	data->scene_img.ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->scene_img.pixels = mlx_get_data_addr(data->scene_img.ptr,
								&data->scene_img.bits_per_pixel,
								&data->scene_img.line_length,
								&data->scene_img.endian);
}

bool	hit_objects(t_data *data, t_ray ray, t_hit_record *rec)
{
	t_list 		*lst;
	float		t;
	float		closest_t;
	t_shapes	*shp;

	lst = data->shapes;
	closest_t = FLT_MAX;
	rec->hit = false;
	shp = NULL;
	while (lst)
	{
		shp = (t_shapes *)lst->content;
		if (ft_strncmp(shp->identifier, "sp", 2) == 0)
		{
			if (ray_inter_sp(ray, shp, &t) && t < closest_t)
			{
				closest_t = t;
				rec->t = t;
				rec->object = shp;
				rec->hit = true;
			}	
		}
		lst = lst->next;
	}
	return (rec->hit);
}

int	ray_color(t_ray ray, t_data *data)
{
	t_hit_record	rec;

	if (hit_objects(data, ray, &rec))
	{
		return (make_color(rec.object->rgb));
	}
	else
	{
		printf("nope\n");
		return(0xFFFFFFFF);
	}
}

void cast_rays(t_data *data)
{
    int     w;
    int     h;
    t_ray   ray;
	int		color;

	init_scene_img(data);

    w = h = 0;
    while (w < WIN_WIDTH)
    {
		h = 0;
        while (h < WIN_HEIGHT)
        {
            ray = shoot_ray(w, h, data);
			color = ray_color(ray, data);
			mrt_put_pixel(&(data->scene_img), w, h, color);
            h++;
        }
        w++;
    }
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->scene_img.ptr, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (-1);
	if (init_program(data, argc, argv) == -1)
		exit(-1);
	if (init_mlx_window(data) == -1)
		exit(-1);
    //place_images(data);
    cast_rays(data);
	mlx_key_hook(data->win_ptr, &key_exit, (void *)data);
	mlx_mouse_hook(data->win_ptr, &check_mouse_button, (void *)data);
	//mlx_hook(data->win_ptr, 33, 1L << 17, &mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//mlx_destroy_display(data->mlx_ptr);
	free_data(data);
	//exit(0);
	return (0);
}
