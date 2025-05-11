/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/11 12:41:52 by aevstign         ###   ########.fr       */
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

void	init_scene_img(t_data *data)
{

	data->scene_img[data->frame % 2]->mlx_ptr = data->mlx_ptr;
	data->scene_img[data->frame % 2]->ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->scene_img[data->frame % 2]->pixels = mlx_get_data_addr(data->scene_img[data->frame % 2]->ptr,
                                                                 &data->scene_img[data->frame % 2]->bits_per_pixel,
                                                                 &data->scene_img[data->frame % 2]->line_length,
                                                                 &data->scene_img[data->frame % 2]->endian);
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
                rec->point = add(ray.origin, scale(ray.dir, t));
				rec->normal = normalize(vec_sub(rec->point, shp->cords));
				closest_t = t;
				rec->t = t;
				rec->object = shp;
				rec->hit = true;
			}	
		}
		else if (ft_strncmp(shp->identifier, "pl", 2) == 0)
		{
			if (ray_inter_pl(ray, shp, &t) && t < closest_t)
			{
				rec->point = add(ray.origin, scale(ray.dir, t));
				rec->normal = normalize(shp->axis);
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

int min(int a, int b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

int max(int a, int b)
{
    if (a > b)
        return (a);
    else
        return (b);
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
			mrt_put_pixel(data->scene_img[data->frame % 2], w, h, color);
            h++;
        }
        w++;
    }
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->scene_img[data->frame % 2]->ptr, 0, 0);
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
	mlx_key_hook(data->win_ptr, &key_mapping, (void *)data);
	mlx_mouse_hook(data->win_ptr, &check_mouse_button, (void *)data);
	//mlx_hook(data->win_ptr, 33, 1L << 17, &mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//mlx_destroy_display(data->mlx_ptr);
	free_data(data);
	//exit(0);
	return (0);
}
