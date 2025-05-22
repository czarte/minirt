/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/22 17:31:52 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minirt.h"

void	resolve_hit(t_hit_record *rec, float t, t_ray ray, t_shapes *shp)
{
	rec->point = add(ray.origin, scale(ray.dir, t));
	rec->t = t;
	rec->object = shp;
	rec->hit = true;
}

void	do_hit(t_ray ray, t_hit_record *rec, float *closest_t, t_shapes *shp)
{
	float		t;

	if ((ft_strncmp(shp->identifier, "sp", 2) == 0)
		&& (ray_inter_sp(ray, shp, &t) && t < *closest_t))
	{
		*closest_t = t;
		resolve_hit(rec, t, ray, shp);
		rec->normal = normalize(vec_sub(rec->point, shp->cords));
	}
	else if ((ft_strncmp(shp->identifier, "pl", 2) == 0)
		&& (ray_inter_pl(ray, shp, &t) && t < *closest_t))
	{
		*closest_t = t;
		resolve_hit(rec, t, ray, shp);
		rec->normal = normalize(shp->axis);
	}
	if ((ft_strncmp(shp->identifier, "cy", 2) == 0)
		&& (ray_inter_cy(ray, shp, &t) && t < *closest_t))
	{
		*closest_t = t;
		resolve_hit(rec, t, ray, shp);
		rec->normal = normalize(vec_sub(rec->point, shp->cords));
	}
}

bool	hit_objects(t_data *data, t_ray ray, t_hit_record *rec)
{
	t_list		*lst;
	float		closest_t;
	t_shapes	*shp;

	lst = data->shapes;
	closest_t = FLT_MAX;
	rec->hit = false;
	shp = NULL;
	while (lst)
	{
		shp = (t_shapes *)lst->content;
		do_hit(ray, rec, &closest_t, shp);
		lst = lst->next;
	}
	return (rec->hit);
}

void	cast_rays(t_data *data)
{
	int		w;
	int		h;
	t_ray	ray;
	int		color;

	init_scene_img(data);
	w = 0;
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->scene_img[data->frame % 2]->ptr, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (-1);
	memset(data, 0, sizeof(t_data));
	if (init_program(data, argc, argv) == -1)
		exit(-1);
	if (init_mlx_window(data) == -1)
		exit(-1);
	cast_rays(data);
	mlx_key_hook(data->win_ptr, &key_mapping, (void *)data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_data(data);
	return (0);
}
