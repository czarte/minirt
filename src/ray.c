/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:28:24 by aevstign          #+#    #+#             */
/*   Updated: 2025/04/22 11:45:04 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec   at(t_ray ray, double t)
{
    t_vec   result;
    
    result = scale(ray.direction, t);
    result = add(ray.origin, result);
    return (result);
}