/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_products.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/04 13:01:46 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minirt.h"
#include "../../include/vec.h"

t_vec	add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec   vec_sub(t_vec a, t_vec b)
{
    return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	cross(t_vec a, t_vec b)
{
	return ((t_vec){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, \
	a.x * b.y - a.y * b.x});
}

t_vec	scale(t_vec a, double s)
{
	return ((t_vec){ a.x * s, a.y * s, a.z * s});
}

t_vec	normalize(t_vec a)
{
	float length = vec_length(&a);
    if (length == 0)
        return ((t_vec){0, 0, 0});
    return (scale(a, 1.0 / length));
}

t_vec	*divide_by_scalar(t_vec *a, float s)
	return (vec3(a->x / s, a->y / s, a->z / s));

t_vec	*substract(t_vec *a, t_vec *b)
	return (vec3(a.x - b->x, a->y - b->y, a.z - b->z));
