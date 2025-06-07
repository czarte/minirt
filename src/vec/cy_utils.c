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
	t_cap_bag	cb;

	cb.r2 = (shp->diameter * 0.5f) * (shp->diameter * 0.5f);
	cb.bias = 0.0001f;
	b.half_h = shp->height * 0.5f;
	b.nor_cyl = normalize(shp->axis);
	hit->t = FLT_MAX;
	hit->hit = false;
	for (int i = 0; i < 2; i++)
	{
		cb.sign = 1.0f;
		if (i == 0)
			cb.sign = -1.0f;
		cb.cap_center = add(shp->cords, scale(b.nor_cyl, cb.sign * cb.half_h));
		cb.denom = vec_dot(&ray.dir, &b.nor_cyl);
		if (fabs(cb.denom) < 0.00001f)
			continue ;
		cb.sub = vec_sub(cb.cap_center, ray.origin);
		cb.t_cap = vec_dot(&cb.sub, &b.nor_cyl) / cb.denom;
		if (cb.t_cap < 0.0f)
			continue ;
		cb.lp = add(ray.origin, scale(ray.dir, cb.t_cap));
		cb.dist = vec_sub(cb.lp, cb.cap_center);
		if (vec_dot(&cb.dist, &cb.dist) <= cb.r2 && cb.t_cap < hit->t)
		{
			cb.cap_normal = normalize(scale(b.nor_cyl, cb.sign));
			if (vec_dot(&ray.dir, &cb.cap_normal) > 0.0f)
				cb.cap_normal = scale(cb.cap_normal, -1.0f);
			hit->t = cb.t_cap;
			hit->normal = cb.cap_normal;
			hit->point = add(cb.lp, scale(cb.cap_normal, cb.bias));
			hit->is_cap = true;
			hit->object = shp;
			hit->hit = true;
		}
	}
	if (hit->hit)
		return (hit->t);
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
