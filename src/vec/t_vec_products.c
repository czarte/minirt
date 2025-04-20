/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_products.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:28:24 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/05 18:28:24 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/vec.h"

t_vec	*add(t_vec *a, t_vec *b)
{
	return (new_vec(a->x + b->x, a->y + b->y, a->z + b->z));
}

t_vec   *vec_sub(t_vec *a, t_vec *b)
{
    return (new_vec(a->x - b->x, a->y - b->y, a->z - b->z));
}

t_vec	*cross(t_vec *a, t_vec *b)
{
	return (new_vec(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, \
	a->x * b->y - a->y * b->x));
}

t_vec	*scale(t_vec *a, double s)
{
	return (new_vec(a->x * s, a->y * s, a->z * s));
}

t_vec	*normalize(t_vec *a)
{
	return (scale(a, vec_length(a)));
}
