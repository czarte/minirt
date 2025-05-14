/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:29:07 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/14 19:13:33 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/vec.h"
#include <math.h>
#include <float.h>

t_ray	shoot_ray(int x, int y, t_data *data)
{
	float	aspect = (float) WIN_WIDTH / WIN_HEIGHT;
	float	fov_radians = (data->scene->cam.fov * M_PI) / 180.0;
	float	scale = tanf(fov_radians / 2);
	float	nor_x = (2 * (x + 0.5) / (float) WIN_WIDTH - 1) * aspect * scale;
	float	nor_y = (1 - 2 * (y + 0.5) / (float) WIN_HEIGHT) * scale;
	t_vec	canvas_point = (t_vec){nor_x, nor_y, -1};
	t_vec	direction = normalize(canvas_point);

	return ((t_ray){data->scene->cam.cords, direction});
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
bool    ray_inter_cy(t_ray ray, t_shapes *shp, float *t) {
    float t1;
    float t2;
    float radius = shp->diameter / 2;
    t_vec oc = vec_sub(ray.origin, shp->cords);
    t_vec nor_cyl = normalize(shp->cords);
    t_vec a = vec_sub(ray.dir, scale(nor_cyl, vec_dot(&ray.dir, &nor_cyl)));
    t_vec b = vec_sub(oc, scale(nor_cyl, vec_dot(&oc, &nor_cyl)));
    float a_f = vec_dot(&a, &a);
    float b_f = 2.0f * vec_dot(&a, &b);
    float c_f = vec_dot(&b, &b) - radius * radius;
    float discriminant = b_f * b_f - 4 * a_f * c_f;

    if (discriminant < 0) return false;

    float sqrt_disc = sqrtf(discriminant);
    t1 = (-b_f - sqrt_disc) / (2 * a_f);
    t2 = (-b_f + sqrt_disc) / (2 * a_f);

    float t_candidates[2] = { t1, t2 };
    for (int i = 0; i < 2; ++i) {
        float ti = t_candidates[i];
        if (ti < 0) continue;
        t_vec p = add(ray.origin, scale(ray.dir, ti));
        t_vec p_b = vec_sub(p, shp->cords);
        float height = vec_dot(&p_b, &nor_cyl);
        if (height >= 0 && height <= shp->height) {
            *t = ti;
            return (true);
        }
    }

    for (int i = 0; i < 2; i++) {
        t_vec cap_center = add(shp->cords, scale(nor_cyl, i * shp->height));
        float denom = vec_dot(&ray.dir, &nor_cyl);
        if (fabs(denom) < EPSILON) continue;

        t_vec sub = vec_sub(cap_center, ray.origin);
        float t_cap = vec_dot(&sub, &nor_cyl) / denom;
        if (t_cap < 0) continue;
        t_vec mul = scale(ray.dir, t_cap);
        t_vec p = add(ray.origin, mul);
        if (vec_length(vec_sub(p, cap_center)) <= radius) {
            *t = t_cap;
            return true;
        }
    }

    return false;
}
