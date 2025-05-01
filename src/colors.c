/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:17:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/01 13:40:47 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	make_color(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

t_rgb calculate_ambient(t_data *data, t_shapes *shp)
{
    t_rgb ambient_color;

    ambient_color.r = (int)(data->scene->ambi.ratio * (float) data->scene->ambi.rgb.r * (float) shp->rgb.r / 255.0f);
    ambient_color.g = (int)(data->scene->ambi.ratio * (float) data->scene->ambi.rgb.g * (float) shp->rgb.g / 255.0f);
    ambient_color.b = (int)(data->scene->ambi.ratio * (float) data->scene->ambi.rgb.b * (float) shp->rgb.b / 255.0f);
    return (ambient_color);
}

t_rgb calculate_diffuse(t_data *data, t_vec dir, t_rgb color, t_hit_record *rec)
{
    t_rgb diffuse;
    double factor;

    factor = fmax(0.0, vec_dot(&rec->normal, &dir)); 
    diffuse.r = (int)(data->scene->lght.bright * (float) data->scene->lght.rgb.r * (float) color.r * (float) factor / 255.0f);
    diffuse.g = (int)(data->scene->lght.bright * (float) data->scene->lght.rgb.g * (float) color.g * (float) factor / 255.0f);
    diffuse.b = (int)(data->scene->lght.bright * (float) data->scene->lght.rgb.b * (float) color.b * (float) factor / 255.0f);
    return (diffuse);
}

t_rgb shader(t_rgb color, t_data *data, t_hit_record *rec)
{
    t_vec l_dir;
    t_rgb mix_color;
    t_rgb diffuse;

    l_dir = normalize(vec_sub(data->scene->lght.cords, rec->point));
    mix_color = calculate_ambient(data, rec->object);
    diffuse = calculate_diffuse(data, l_dir, color, rec);
    mix_color.r = min(mix_color.r + diffuse.r, 255);
    mix_color.g = min(mix_color.g + diffuse.g, 255);
    mix_color.b = min(mix_color.b + diffuse.b, 255);
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
