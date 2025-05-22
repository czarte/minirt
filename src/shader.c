/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:17:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/22 17:22:17 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// Compute shadow softness factor:
// - dot(normal, light_dir) gives how directly the surface faces the light (1.0
// = fully facing).
// - fmax ensures we ignore negative values (light from behind).
// - Multiplied by 0.5 to limit the max contribution from this term.
// - Added 0.2 as a base value to keep shadows slightly visible (not pitch
// black).
// Final result ranges from 0.2 (fully in shadow) to 0.7 (partially lit).

t_rgb	shader(t_rgb color, t_data *data, t_hit_record *rec)
{
	t_sbag	sb;

	sb.l_dir = normalize(vec_sub(data->scene->lght.cords, rec->point));
	sb.factor = fmax(0.0, vec_dot(&rec->normal, &sb.l_dir));
	sb.mix_color = calculate_ambient(data, rec->object);
	if (is_in_shadow(data, rec->point, data->scene->lght.cords, rec->normal))
	{
		sb.softness = 0.2f + 0.5f * fmax(0.0, vec_dot(&rec->normal, &sb.l_dir));
		sb.visibility = 0.2f;
		sb.factor *= sb.visibility;
		sb.diffuse = calculate_diffuse(data, sb.l_dir, color, rec);
		sb.diffuse.r *= sb.softness;
		sb.diffuse.g *= sb.softness;
		sb.diffuse.b *= sb.softness;
	}
	else
		sb.diffuse = calculate_diffuse(data, sb.l_dir, color, rec);
	sb.mix_color.r = min(sb.mix_color.r * 0.4f + sb.diffuse.r * sb.factor, 255);
	sb.mix_color.g = min(sb.mix_color.g * 0.4f + sb.diffuse.g * sb.factor, 255);
	sb.mix_color.b = min(sb.mix_color.b * 0.4f + sb.diffuse.b * sb.factor, 255);
	return (sb.mix_color);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
