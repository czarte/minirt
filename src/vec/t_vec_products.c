/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_products.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:28:24 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/14 22:43:33 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/vec.h"

/*
Create a 3D vector struct that support following operations:

Vector Addition
Vector Subtraction
Vector Magnitude
Dot Product
Vector Normalization
Vector Multiplication (Multiplying a Vector by a scalar)
*/

t_vec	*add(t_vec *a, t_vec *b) {
    return (new_vec(a->x + b->x, a->y + b->y, a->z + b->z));
}

t_vec	*cross(t_vec *a, t_vec *b) {
	return (new_vec(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x));
}

// If you alloc new_vec here we need to check every time check it it is not NULL
t_vec	*scale(t_vec *a, double s) {
	return(new_vec(a->x * s, a->y * s, a->z * s));
}

t_vec	*normalize(t_vec *a) {
	return(scale(a, vec_length(a)));
}

t_vec	divide_by_scalar(t_vec a, float s)
{
	return (vec3(a.x / s, a.y / s, a.z / s));
}

t_vec	substract(t_vec a, t_vec b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}
