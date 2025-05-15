/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:29:07 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/11 12:22:46 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/vec.h"
#include <math.h>

t_ray	shoot_ray(int x, int y, t_data *data)
{
	float	aspect = (float) WIN_WIDTH / WIN_HEIGHT;
	float	fov_radians = data->scene->cam.fov * (M_PI / 180.0);
	float	scale_fov = tanf(fov_radians / 2);
	float	nor_x = (2.0f * (x + 0.5f) / (float) WIN_WIDTH - 1.0f) * aspect * scale_fov;
	float	nor_y = (1.0f - 2.0f * (y + 0.5) / (float) WIN_HEIGHT) * scale_fov;
	//t_vec	canvas_point = (t_vec){nor_x, nor_y, -1};
	t_vec	direction; //= normalize( add(add(scale(data->scene->cam.right, nor_x), scale(data->scene->cam.up, nor_y)), data->scene->cam.orient ));
    direction = add(data->scene->cam.orient, scale(data->scene->cam.right, nor_x));
    direction = add(direction, scale(data->scene->cam.up, nor_y));


    //normalize(canvas_point);

    //return ((t_ray){data->scene->cam.cords, direction});
	return ((t_ray){data->scene->cam.cords, normalize(direction)});
}

bool	ray_inter_sp(t_ray ray, t_shapes *shp, float *t)
{
	float	t1;
	float	t2;
	float	shp_radius = shp->diameter / 2;
    t_vec oc = vec_sub(ray.origin, shp->cords);
    float a = vec_dot(&ray.dir, &ray.dir);
    float b = 2.0f * vec_dot(&ray.dir, &oc);
    float c = vec_dot(&oc, &oc) - shp_radius * shp_radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 > 0.001f) {
        *t = t1;
        return true;
    } else if (t2 > 0.001f) {
        *t = t2;
        return true;
    }
    return false;
}

bool	ray_inter_pl(t_ray ray, t_shapes *shp, float *t)
{
	float	denom;
	t_vec	oc;
	float	numer;

	oc = vec_sub(shp->cords, ray.origin);
	denom = vec_dot(&ray.dir, &shp->axis);
	if (fabs(denom) < 1e-6)
		return (false);
	numer = vec_dot(&shp->axis, &oc);
	*t = numer / denom;
	return (*t > 0.001f);
}
