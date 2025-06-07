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

void	calculate_cy_bag(t_cybag *b, t_shapes *shp, t_ray ray)
{
	b->radius = shp->diameter / 2.0f;
	b->nor_cyl = normalize(shp->axis);
	b->oc = vec_sub(ray.origin, shp->cords);
	b->a = vec_sub(ray.dir, scale(b->nor_cyl, vec_dot(&ray.dir, &b->nor_cyl)));
	b->b = vec_sub(b->oc, scale(b->nor_cyl, vec_dot(&b->oc, &b->nor_cyl)));
	b->a_f = vec_dot(&b->a, &b->a);
	b->b_f = 2.0f * vec_dot(&b->a, &b->b);
	b->c_f = vec_dot(&b->b, &b->b) - b->radius * b->radius;
	b->discriminant = b->b_f * b->b_f - 4 * b->a_f * b->c_f;
}

bool ray_inter_cy(t_ray ray, t_shapes *shp, float *t, t_hit_record *rec)
{
	t_cybag b;
	t_hit_record rec_body, rec_cap;
	float t_body = -1.0f, t_cap = -1.0f;

	calculate_cy_bag(&b, shp, ray);

	if (b.discriminant >= 0.0f)
	{
		b.sqrt_disc = sqrtf(b.discriminant);
		b.t1 = (-b.b_f - b.sqrt_disc) / (2.0f * b.a_f);
		b.t2 = (-b.b_f + b.sqrt_disc) / (2.0f * b.a_f);
		b.t_candidates[0] = b.t1;
		b.t_candidates[1] = b.t2;

		t_body = process_cy_body(b, shp, ray);
		if (t_body > 0.0f)
		{
			resolve_hit(&rec_body, t_body, ray, shp);

			t_vec to_point = vec_sub(rec_body.point, shp->cords);
			t_vec projection = scale(b.nor_cyl, vec_dot(&to_point, &b.nor_cyl));
			rec_body.normal = normalize(vec_sub(to_point, projection));
		}
	}

	t_cap = process_cy_cap(b, shp, ray, &rec_cap);

	if (t_body > 0.0f && (t_cap < 0.0f || t_body < t_cap))
	{
		*rec = rec_body;
		*t = t_body;
		return true;
	}
	else if (t_cap > 0.0f)
	{
		*rec = rec_cap;
		*t = t_cap;
		return true;
	}
	return false;
}

