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
			if (ray_inter_sp(ray, shp, &t, rec) && t < closest_t)
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

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

t_rgb calculate_diffuse(t_data *data, t_vec *dir, t_rgb color, t_hit_record *rec) {
    t_rgb diffuse;
    double factor;

    factor = vec_dot(rec->normal, dir);
    diffuse.r = (int)(data->scene->lght.bright * data->scene->lght.rgb.r * color.r * factor / 255.0);
    diffuse.g = (int)(data->scene->lght.bright * data->scene->lght.rgb.g * color.r * factor / 255.0);
    diffuse.b = (int)(data->scene->lght.bright * data->scene->lght.rgb.b * color.r * factor / 255.0);
    return (diffuse);
}

t_rgb shader(t_rgb color, t_data *data, t_hit_record *rec)
{
    t_vec *l_dir;
    t_rgb mix_color;
    t_rgb diffuse;

    l_dir = vec_sub(&data->scene->lght.cords, rec->point);
    normalize(l_dir);
    diffuse = calculate_diffuse(data, l_dir, color, rec);
    mix_color.r = min(data->scene->ambi.rgb.r + diffuse.r, 255);
    mix_color.g = min(data->scene->ambi.rgb.g + diffuse.g, 255);
    mix_color.b = min(data->scene->ambi.rgb.b + diffuse.b, 255);
    return (mix_color);
}

int	ray_color(t_ray ray, t_data *data)
{
	t_hit_record	rec;

	if (hit_objects(data, ray, &rec))
	{
		return (make_color(shader(rec.object->rgb, data, &rec)));
	}
	else
	{
//		printf("nope\n");
		return(make_color(data->scene->ambi.rgb)*data->scene->ambi.ratio);
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
