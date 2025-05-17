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
	b->radius = shp->diameter / 2;
	b->oc = vec_sub(ray.origin, shp->cords);
	b->nor_cyl = normalize(shp->cords);
	b->a = vec_sub(ray.dir, scale(b->nor_cyl, vec_dot(&ray.dir, &b->nor_cyl)));
	b->b = vec_sub(b->oc, scale(b->nor_cyl, vec_dot(&b->oc, &b->nor_cyl)));
	b->a_f = vec_dot(&b->a, &b->a);
	b->b_f = 2.0f * vec_dot(&b->a, &b->b);
	b->c_f = vec_dot(&b->b, &b->b) - b->radius * b->radius;
	b->discriminant = b->b_f * b->b_f - 4 * b->a_f * b->c_f;
}

//bool	ray_inter_cy(t_ray ray, t_shapes *shp, float *t)
//{
//	t_cybag	b;
//	float	crb;
//
//	calculate_cy_bag(&b, shp, ray);
//	if (b.discriminant < 0)
//		return (false);
//	b.sqrt_disc = sqrtf(b.discriminant);
//	b.t1 = (-b.b_f - b.sqrt_disc) / (2 * b.a_f);
//	b.t2 = (-b.b_f + b.sqrt_disc) / (2 * b.a_f);
//	b.t_candidates[0] = b.t1;
//	b.t_candidates[1] = b.t2;
//	crb = process_cy_body(b, shp, ray);
//	if (crb > 0)
//	{
//		*t = crb;
//		return (true);
//	}
//	crb = process_cy_cap(b, shp, ray);
//	if (crb > 0)
//	{
//		*t = crb;
//		return (true);
//	}
//	return (false);
//}

float	process_cy_cap(t_cybag b, t_shapes *shp, t_ray ray)
{
	int i;

	i = 0;
	while (i < 2)
	{
		b.cap_center = add(shp->cords, scale(b.nor_cyl, i * shp->height));
		b.denom = vec_dot(&ray.dir, &b.nor_cyl);
		if (fabs(b.denom) < EPSILON) {
			i++;
			continue;
		}
		b.sub = vec_sub(b.cap_center, ray.origin);
		b.t_cap = vec_dot(&b.sub, &b.nor_cyl) / b.denom;
		if (b.t_cap < 0) {
			i++;
			continue;
		}
		b.mul = scale(ray.dir, b.t_cap);
		b.lp = add(ray.origin, b.mul);
		if (vec_length(vec_sub(b.lp, b.cap_center)) <= b.radius)
			return (b.t_cap);
		i++;
	}
	return (-1.0f);
}

float	process_cy_body(t_cybag b, t_shapes *shp, t_ray ray)
{
	for (int i = 0; i < 2; ++i)
	{
		b.ti = b.t_candidates[i];
		if (b.ti < 0)
			continue ;
		b.p = add(ray.origin, scale(ray.dir, b.ti));
		b.p_b = vec_sub(b.p, shp->cords);
		b.height = vec_dot(&b.p_b, &b.nor_cyl);
		if (b.height >= 0 && b.height <= shp->height)
			return (b.ti);
	}
	return (-1.0f);
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
