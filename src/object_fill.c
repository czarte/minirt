/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:35:45 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/17 14:25:00 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	tvec_from_split(t_vec *v, char **split)
{
	int	j;

	j = 0;
	v->x = ft_atof(split[0]);
	v->y = ft_atof(split[1]);
	v->z = ft_atof(split[2]);
	while (j < 3)
	{
		free(split[j]);
		j++;
	}
}

void	trgb_from_split(t_rgb *rgb, char **split)
{
	int	j;

	j = 0;
	rgb->alpha = 1;
	rgb->r = ft_atoi(split[0]);
	rgb->g = ft_atoi(split[1]);
	rgb->b = ft_atoi(split[2]);
	while (j < 3)
	{
		free(split[j]);
		j++;
	}
}

void	iter_pl(t_data *data, char *tmp, t_shapes *pl_shape)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	check_scene_alloc(data, ob);
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		read_next_word(tmp, ob);
		process_pl(data, pl_shape, ob);
		ob->k++;
	}
	free(ob);
}

void	iter_sp(t_data *data, char *tmp, t_shapes *sp_shape)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	check_scene_alloc(data, ob);
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		read_next_word(tmp, ob);
		process_sp(data, sp_shape, ob);
		ob->k++;
	}
	free(ob);
}

void	iter_cy(t_data *data, char *tmp, t_shapes *cy_shape)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	check_scene_alloc(data, ob);
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		do_j_bzero(ob);
		move_cp_buf(tmp, ob);
		process_cy(data, cy_shape, ob);
		ob->k++;
	}
	free(ob);
}
