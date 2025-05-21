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

float	process_cy_cap(t_cybag b, t_shapes *shp, t_ray ray)
{
	b.i = 0;
	while (b.i < 2)
	{
		b.cap_center = add(shp->cords, scale(b.nor_cyl, b.i * shp->height));
		b.denom = vec_dot(&ray.dir, &b.nor_cyl);
		if (fabs(b.denom) < EPSILON)
		{
			b.i++;
			continue ;
		}
		b.sub = vec_sub(b.cap_center, ray.origin);
		b.t_cap = vec_dot(&b.sub, &b.nor_cyl) / b.denom;
		if (b.t_cap < 0)
		{
			b.i++;
			continue ;
		}
		b.mul = scale(ray.dir, b.t_cap);
		b.lp = add(ray.origin, b.mul);
		if (vec_length(vec_sub(b.lp, b.cap_center)) <= b.radius)
			return (b.t_cap);
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
		if (b.height >= 0 && b.height <= shp->height)
			return (b.ti);
		++b.i;
	}
	return (-1.0f);
}
