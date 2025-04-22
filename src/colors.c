/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:17:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/22 11:57:05 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	make_color(t_rgb rgb)
{
	int	color;

	color = (0x000000 + rgb.r) << 16;
	color += (0x00 + rgb.g) << 8;
	color += (0x00 + rgb.b);
	return (color);
}

double  clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
