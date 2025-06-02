/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:12:32 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/31 14:15:30 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec.h"
#include "../../include/minirt.h"

float	process_cy_cap(t_cybag b, t_shapes *shp, t_ray ray, t_hit_record *hit)
{
	b.half_h = shp->height / 2.0f;
	b.i = 0;
	while (b.i < 2)
	{
		if (b.i == 0)
			b.sign = -1.0f;
		else
			b.sign = 1.0f;
		b.cap_center = add(shp->cords, scale(b.nor_cyl, b.sign * b.half_h));
		b.denom = vec_dot(&ray.dir, &b.nor_cyl);
		b.sub = vec_sub(b.cap_center, ray.origin);
		b.t_cap = vec_dot(&b.sub, &b.nor_cyl) / b.denom;
		if (b.t_cap < 0 || fabs(b.denom) < EPSILON)
		{
			b.i++;
			continue ;
		}
		b.mul = scale(ray.dir, b.t_cap);
		b.lp = add(ray.origin, b.mul);
		t_vec dist = vec_sub(b.lp, b.cap_center);
		if (vec_dot(&dist, &dist) <= b.radius * b.radius) {
			printf("Testing cap %d: t_cap=%.4f, lp=(%.2f,%.2f,%.2f), center=(%.2f,%.2f,%.2f), dist=%.4f\n",
				   b.i, b.t_cap, b.lp.x, b.lp.y, b.lp.z, b.cap_center.x, b.cap_center.y, b.cap_center.z,
				   vec_length(vec_sub(b.lp, b.cap_center)));
			hit->t = b.t_cap;
			hit->point = b.lp;
			//hit->normal = scale(b.nor_cyl, b.sign);
			t_vec cap_normal = scale(b.nor_cyl, b.sign);
			if (vec_dot(&ray.dir, &cap_normal) > 0)
				cap_normal = scale(cap_normal, -1);  // flip if needed
			hit->normal = cap_normal;
			hit->is_cap = true;
			return (b.t_cap);
		}
		b.i++;
	}
	return (-1.0f);
}

float	process_cy_body(t_cybag b, t_shapes *shp, t_ray ray)
{
	b.i = 0;
	while (b.i < 2)
	{
		b.ti = b.t_candidates[b.i];
		if (b.ti < 0)
		{
			b.i++;
			continue ;
		}
		b.p = add(ray.origin, scale(ray.dir, b.ti));
		b.p_b = vec_sub(b.p, shp->cords);
		b.height = vec_dot(&b.p_b, &b.nor_cyl);
		if (b.height >= -shp->height / 2.0f && b.height <= shp->height / 2.0f)
			return (b.ti);
		++b.i;
	}
	return (-1.0f);
}
