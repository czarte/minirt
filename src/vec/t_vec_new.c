/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:36:49 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/22 12:21:46 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec.h"
#include "../../include/minirt.h"

t_vec	*new_vec(float x, float y, float z)
{
	t_vec	*r;

    r = malloc(sizeof(t_vec));
    if (!r)
        return (NULL);
    r->x = x;
    r->y = y;
    r->z = z;
    return (r);
}

t_vec   vec3(float x, float y, float z)
{
    t_vec   r;

    r.x = x;
    r.y = y;
    r.z = z;
    return (r); 
}
