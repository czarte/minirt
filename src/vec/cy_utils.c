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

float process_cy_cap(t_cybag b, t_shapes *shp, t_ray ray, t_hit_record *hit)
{
	t_vec cap_center, dist, lp, cap_normal, sub;
	float t_cap, half_h, denom;
	int i;
	float r2 = (shp->diameter * 0.5f) * (shp->diameter * 0.5f);
	const float bias = 0.0001f;  // Жёстко заданное смещение

	half_h = shp->height * 0.5f;
	b.nor_cyl = normalize(shp->axis);

	hit->t = FLT_MAX;
	hit->hit = false;

	for (i = 0; i < 2; i++)
	{
		float sign = (i == 0) ? -1.0f : 1.0f;
		cap_center = add(shp->cords, scale(b.nor_cyl, sign * half_h));
		denom = vec_dot(&ray.dir, &b.nor_cyl);

		if (fabs(denom) < 0.00001f)
			continue;

		sub = vec_sub(cap_center, ray.origin);
		t_cap = vec_dot(&sub, &b.nor_cyl) / denom;

		if (t_cap < 0.0f)
			continue;

		lp = add(ray.origin, scale(ray.dir, t_cap));
		dist = vec_sub(lp, cap_center);

		if (vec_dot(&dist, &dist) <= r2 && t_cap < hit->t)
		{
			cap_normal = normalize(scale(b.nor_cyl, sign));

			if (vec_dot(&ray.dir, &cap_normal) > 0.0f)
				cap_normal = scale(cap_normal, -1.0f);

			hit->t = t_cap;
			hit->normal = cap_normal;
			hit->point = add(lp, scale(cap_normal, bias));  // Смещение точки вдоль нормали
			hit->is_cap = true;
			hit->object = shp;
			hit->hit = true;
		}
	}

	return (hit->hit ? hit->t : -1.0f);
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
