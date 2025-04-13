/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:36:49 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/05 18:38:15 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec.h"
#include "../../include/minirt.h"

t_vec	*new_vec(float x, float y, float z)
{
	t_vec	*r;

	r = malloc(sizeof(t_vec));
	r->x = x;
	r->y = y;
	r->z = z;
	return (r);
}
