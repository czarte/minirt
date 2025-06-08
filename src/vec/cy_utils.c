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

static void	check_cy_cap_hit(t_cap_hit_ctx ctx)
{
	ctx.cb->cap_center = add(ctx.shp->cords,
			scale(ctx.b->nor_cyl, ctx.cb->sign * ctx.cb->half_h));
	ctx.cb->denom = vec_dot(&ctx.ray.dir, &ctx.b->nor_cyl);
	if (fabs(ctx.cb->denom) < 0.00001f)
		return ;
	ctx.cb->sub = vec_sub(ctx.cb->cap_center, ctx.ray.origin);
	ctx.cb->t_cap = vec_dot(&ctx.cb->sub, &ctx.b->nor_cyl) / ctx.cb->denom;
	if (ctx.cb->t_cap < 0.0f)
		return ;
	ctx.cb->lp = add(ctx.ray.origin, scale(ctx.ray.dir, ctx.cb->t_cap));
	ctx.cb->dist = vec_sub(ctx.cb->lp, ctx.cb->cap_center);
	if (vec_dot(&ctx.cb->dist, &ctx.cb->dist) > ctx.cb->r2
		|| ctx.cb->t_cap >= ctx.hit->t)
		return ;
	ctx.cb->cap_normal = normalize(scale(ctx.b->nor_cyl, ctx.cb->sign));
	if (vec_dot(&ctx.ray.dir, &ctx.cb->cap_normal) > 0.0f)
		ctx.cb->cap_normal = scale(ctx.cb->cap_normal, -1.0f);
	ctx.hit->t = ctx.cb->t_cap;
	ctx.hit->normal = ctx.cb->cap_normal;
	ctx.hit->point = add(ctx.cb->lp, scale(ctx.cb->cap_normal, ctx.cb->bias));
	ctx.hit->is_cap = true;
	ctx.hit->object = ctx.shp;
	ctx.hit->hit = true;
}

float	process_cy_cap(t_cybag b, t_shapes *shp, t_ray ray, t_hit_record *hit)
{
	t_cap_bag		cb;
	t_cap_hit_ctx	ctx;
	int				i;

	cb.r2 = (shp->diameter * 0.5f) * (shp->diameter * 0.5f);
	cb.bias = 0.0001f;
	cb.half_h = shp->height * 0.5f;
	b.nor_cyl = normalize(shp->axis);
	hit->t = FLT_MAX;
	hit->hit = false;
	ctx = (t_cap_hit_ctx){&cb, &b, shp, ray, hit};
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			cb.sign = -1.0f;
		else
			cb.sign = 1.0f;
		check_cy_cap_hit(ctx);
		i++;
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

void	calculate_cy_bag(t_cybag *b, t_shapes *shp, t_ray ray)
{
	b->t_body = -1.0f;
	b->t_cap = -1.0f;
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

void	handle_cy_body(t_cybag *b, t_shapes *shp, t_ray ray)
{
	t_vec	to_point;
	t_vec	projection;

	b->t_body = process_cy_body(*b, shp, ray);
	if (b->t_body <= 0.0f)
		return ;
	resolve_hit(&b->rec_body, b->t_body, ray, shp);
	to_point = vec_sub(b->rec_body.point, shp->cords);
	projection = scale(b->nor_cyl, vec_dot(&to_point, &b->nor_cyl));
	b->rec_body.normal = normalize(vec_sub(to_point, projection));
}
