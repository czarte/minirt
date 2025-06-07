/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:28:10 by voparkan          #+#    #+#             */
/*   Updated: 2025/06/07 14:33:25 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:17:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/06 16:20:44 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	make_color(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

t_rgb	calculate_ambient(t_data *data, t_shapes *shp)
{
	t_rgb	ambient_color;

	ambient_color.r = (int)(data->scene->ambi.ratio * (float) \
		data->scene->ambi.rgb.r * (float) shp->rgb.r / 255.0f);
	ambient_color.g = (int)(data->scene->ambi.ratio * (float) \
		data->scene->ambi.rgb.g * (float) shp->rgb.g / 255.0f);
	ambient_color.b = (int)(data->scene->ambi.ratio * (float) \
		data->scene->ambi.rgb.b * (float) shp->rgb.b / 255.0f);
	return (ambient_color);
}

t_rgb	calculate_diffuse(t_data *data, t_vec l_dir, t_rgb color, t_hit_record \
			*rec)
{
	t_rgb	diffuse;
	double	factor;

	factor = fmax(0.0, vec_dot(&rec->normal, &l_dir));
	diffuse.r = (int)(data->scene->lght.bright * (float) \
		data->scene->lght.rgb.r * (float) color.r * (float) factor / 255.0f);
	diffuse.g = (int)(data->scene->lght.bright * (float) \
		data->scene->lght.rgb.g * (float) color.g * (float) factor / 255.0f); //
	diffuse.b = (int)(data->scene->lght.bright * (float) \
		data->scene->lght.rgb.b * (float) color.b * (float) factor / 255.0f); //
	return (diffuse);
}

bool	is_in_shadow(t_data *data, t_vec point, t_vec light_pos, t_vec normal)
{
	t_vec			to_light;
	t_ray			shadow_ray;
	double			light_dist;
	t_hit_record	tmp;
	double			hit_dist;

	if (data->scene->ambi.ratio == 1)
		return (false);
	to_light = vec_sub(light_pos, point);
	light_dist = vec_length(to_light);
	shadow_ray.origin = add(point, scale(normal, 1e-3));
	shadow_ray.dir = normalize(to_light);
	if (hit_objects(data, shadow_ray, &tmp))
	{
		hit_dist = vec_length(vec_sub(tmp.point, point));
		if (hit_dist < light_dist)
			return (true);
	}
	return (false);
}

int	ray_color(t_ray ray, t_data *data)
{
	t_hit_record	rec;
	t_rgb			bg;

	if (hit_objects(data, ray, &rec))
	{
		return (make_color(shader(rec.object->rgb, data, &rec)));
	}
	else
	{
		bg.r = data->scene->ambi.rgb.r * data->scene->ambi.ratio;
		bg.g = data->scene->ambi.rgb.g * data->scene->ambi.ratio;
		bg.b = data->scene->ambi.rgb.b * data->scene->ambi.ratio;
		return (make_color(bg));
	}
}
