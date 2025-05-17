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
    t_rgb ambient_color;

    ambient_color.r = (int)(data->scene->ambi.ratio * (float) data->scene->ambi.rgb.r * (float) shp->rgb.r / 255.0f);
    ambient_color.g = (int)(data->scene->ambi.ratio * (float) data->scene->ambi.rgb.g * (float) shp->rgb.g / 255.0f);
    ambient_color.b = (int)(data->scene->ambi.ratio * (float) data->scene->ambi.rgb.b * (float) shp->rgb.b / 255.0f);
    return (ambient_color);
}

t_rgb	calculate_diffuse(t_data *data, t_vec l_dir, t_rgb color, t_hit_record *rec)
{
    t_rgb diffuse;
    double factor;

    factor = fmax(0.0, vec_dot(&rec->normal, &l_dir));
    diffuse.r = (int)(data->scene->lght.bright * (float) data->scene->lght.rgb.r * (float) color.r * (float) factor / 255.0f);
    diffuse.g = (int)(data->scene->lght.bright * (float) data->scene->lght.rgb.g * (float) color.g * (float) factor / 255.0f);
    diffuse.b = (int)(data->scene->lght.bright * (float) data->scene->lght.rgb.b * (float) color.b * (float) factor / 255.0f);
    return (diffuse);
}

bool    is_in_shadow(t_data *data, t_vec point, t_vec light_pos, t_vec normal)
{
	t_vec			to_light;
	t_ray			shadow_ray;
	double			light_dist;
	t_hit_record	tmp;
	double			hit_dist;

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

// Compute shadow softness factor:
// - dot(normal, light_dir) gives how directly the surface faces the light (1.0 = fully facing).
// - fmax ensures we ignore negative values (light from behind).
// - Multiplied by 0.5 to limit the max contribution from this term.
// - Added 0.2 as a base value to keep shadows slightly visible (not pitch black).
// Final result ranges from 0.2 (fully in shadow) to 0.7 (partially lit).

t_rgb shader(t_rgb color, t_data *data, t_hit_record *rec)
{
    t_vec l_dir;
    t_rgb mix_color;
    t_rgb diffuse;
    double factor;

    l_dir = normalize(vec_sub(data->scene->lght.cords, rec->point));
    factor = fmax(0.0, vec_dot(&rec->normal, &l_dir));
    mix_color = calculate_ambient(data, rec->object);
	if (is_in_shadow(data, rec->point, data->scene->lght.cords, rec->normal))
	{
	    float softness = 0.2f + 0.5f * fmax(0.0, vec_dot(&rec->normal, &l_dir));
		float visibility = 0.2f;
		factor *= visibility; 
  		diffuse = calculate_diffuse(data, l_dir, color, rec);
   		diffuse.r *= softness;
    	diffuse.g *= softness;
    	diffuse.b *= softness;
	}
	else
    	diffuse = calculate_diffuse(data, l_dir, color, rec);
    mix_color.r = min(mix_color.r * 0.4f + diffuse.r * factor, 255);
    mix_color.g = min(mix_color.g * 0.4f + diffuse.g * factor, 255);
    mix_color.b = min(mix_color.b * 0.4f + diffuse.b * factor, 255);
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
        t_rgb bg = {
            .r = data->scene->ambi.rgb.r * data->scene->ambi.ratio,
            .g = data->scene->ambi.rgb.g * data->scene->ambi.ratio,
            .b = data->scene->ambi.rgb.b * data->scene->ambi.ratio
        };
        return (make_color(bg));
        // return(make_color(data->scene->ambi.rgb)*data->scene->ambi.ratio);
    }
}
