/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:12:32 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/31 15:57:10 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/vec.h"
#include <math.h>

t_ray	shoot_ray(int x, int y, t_data *data)
{
	t_vec	direction;
	t_rbag	rb;

	rb.aspect = (float) WIN_WIDTH / WIN_HEIGHT;
	rb.fov_radians = data->scene->cam.fov * (M_PI / 180.0);
	rb.scale_fov = tanf(rb.fov_radians / 2);
	rb.nor_x = (2.0f * (x + 0.5f) / (float) WIN_WIDTH - 1.0f) * rb.aspect
		* rb.scale_fov;
	rb.nor_y = (1.0f - 2.0f * (y + 0.5) / (float) WIN_HEIGHT) * rb.scale_fov;
	direction = add(data->scene->cam.orient,
			scale(data->scene->cam.right, rb.nor_x));
	direction = add(direction, scale(data->scene->cam.up, rb.nor_y));
	return ((t_ray){data->scene->cam.cords, normalize(direction)});
}

bool	ray_inter_sp(t_ray ray, t_shapes *shp, float *t)
{
	t_spbag	bg;

	bg.shp_radius = shp->diameter / 2;
	bg.oc = vec_sub(ray.origin, shp->cords);
	bg.a = vec_dot(&ray.dir, &ray.dir);
	bg.b = 2.0f * vec_dot(&ray.dir, &bg.oc);
	bg.c = vec_dot(&bg.oc, &bg.oc) - bg.shp_radius * bg.shp_radius;
	bg.discriminant = bg.b * bg.b - 4 * bg.a * bg.c;
	if (bg.discriminant < 0)
		return (false);
	bg.t1 = (-bg.b - sqrt(bg.discriminant)) / (2.0 * bg.a);
	bg.t2 = (-bg.b + sqrt(bg.discriminant)) / (2.0 * bg.a);
	if (bg.t1 > 0.001f)
	{
		*t = bg.t1;
		return (true);
	}
	else if (bg.t2 > 0.001f)
	{
		*t = bg.t2;
		return (true);
	}
	return (false);
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

void	prepare_cy_intersect(t_cybag *b, t_shapes *shp, t_ray ray)
{
	calculate_cy_bag(b, shp, ray);
	if (b->discriminant < 0.0f)
		return ;
	b->sqrt_disc = sqrtf(b->discriminant);
	b->t1 = (-b->b_f - b->sqrt_disc) / (2.0f * b->a_f);
	b->t2 = (-b->b_f + b->sqrt_disc) / (2.0f * b->a_f);
	b->t_candidates[0] = b->t1;
	b->t_candidates[1] = b->t2;
}

bool	ray_inter_cy(t_ray ray, t_shapes *shp, float *t, t_hit_record *rec)
{
	t_cybag	b;

	prepare_cy_intersect(&b, shp, ray);
	if (b.discriminant >= 0.0f)
		handle_cy_body(&b, shp, ray);
	b.t_cap = process_cy_cap(b, shp, ray, &b.rec_cap);
	if (b.t_body > 0.0f && (b.t_cap < 0.0f || b.t_body < b.t_cap))
	{
		*rec = b.rec_body;
		*t = b.t_body;
		return (true);
	}
	if (b.t_cap > 0.0f)
	{
		*rec = b.rec_cap;
		*t = b.t_cap;
		return (true);
	}
	return (false);
}
