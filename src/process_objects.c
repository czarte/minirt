/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:02:19 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/11 16:39:26 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	process_pl(t_data *data, t_shapes *pl_shape, t_obag *ob)
{
	if (ob->k < 3)
	{
		ob->spl_buf = ft_split(ob->buf, ',');
		check_scene_alloc(data, ob->spl_buf);
	}
	ob->j = 0;
	if (ob->k == 0)
		tvec_from_split(&pl_shape->cords, ob->spl_buf);
	if (ob->k == 1)
		tvec_from_split(&pl_shape->axis, ob->spl_buf);
	if (ob->k == 2)
		trgb_from_split(&pl_shape->rgb, ob->spl_buf);
	if (ob->k < 3)
		free(ob->spl_buf);
}

void	process_sp(t_data *data, t_shapes *sp_shape, t_obag *ob)
{
	if (ob->k != 1)
	{
		ob->spl_buf = ft_split(ob->buf, ',');
		check_scene_alloc(data, ob->spl_buf);
	}
	ob->j = 0;
	if (ob->k == 0)
		tvec_from_split(&sp_shape->cords, ob->spl_buf);
	if (ob->k == 1)
		sp_shape->diameter = atof(ob->buf);
	if (ob->k == 2)
		trgb_from_split(&sp_shape->rgb, ob->spl_buf);
	if (ob->k != 1)
		free(ob->spl_buf);
}

void	process_cy(t_data *data, t_shapes *cy_shape, t_obag *ob)
{
	if (ob->k < 2 || ob->k > 3)
	{
		ob->spl_buf = ft_split(ob->buf, ',');
		check_scene_alloc(data, ob->spl_buf);
	}
	ob->j = 0;
	if (ob->k == 0)
		tvec_from_split(&cy_shape->cords, ob->spl_buf);
	if (ob->k == 1)
		tvec_from_split(&cy_shape->axis, ob->spl_buf);
	if (ob->k == 2)
		cy_shape->diameter = atof(ob->buf);
	if (ob->k == 3)
		cy_shape->height = atof(ob->buf);
	if (ob->k == 4)
		trgb_from_split(&cy_shape->rgb, ob->spl_buf);
	if (ob->k < 2 || ob->k > 3)
		free(ob->spl_buf);
}
