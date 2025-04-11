/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:35:45 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/11 16:38:41 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	tvec_from_split(t_vec *v, char **split)
{
	int	j;

	j = 0;
	v->x = atof(split[0]);
	v->y = atof(split[1]);
	v->z = atof(split[2]);
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

void	iter_pl(char *tmp, t_shapes *pl_shape)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		do_j_bzero(ob);
		while (ft_spacious(tmp[ob->i]))
			ob->i++;
		while (tmp[ob->i] && !ft_spacious(tmp[ob->i]))
			ob->buf[ob->j++] = tmp[ob->i++];
		ob->buf[ob->i] = '\0';
		if (ob->k < 3)
			ob->spl_buf = ft_split(ob->buf, ',');
		ob->j = 0;
		if (ob->k == 0)
			tvec_from_split(&pl_shape->cords, ob->spl_buf);
		if (ob->k == 1)
			tvec_from_split(&pl_shape->axis, ob->spl_buf);
		if (ob->k == 2)
			trgb_from_split(&pl_shape->rgb, ob->spl_buf);
		if (ob->k < 3)
			free(ob->spl_buf);
		ob->k++;
	}
}

void	iter_sp(char *tmp, t_shapes *sp_shape)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		do_j_bzero(ob);
		while (ft_spacious(tmp[ob->i]))
			ob->i++;
		while (tmp[ob->i] && !ft_spacious(tmp[ob->i]))
			ob->buf[ob->j++] = tmp[ob->i++];
		ob->buf[ob->i] = '\0';
		if (ob->k != 1)
			ob->spl_buf = ft_split(ob->buf, ',');
		ob->j = 0;
		if (ob->k == 0)
			tvec_from_split(&sp_shape->cords, ob->spl_buf);
		if (ob->k == 1)
			sp_shape->diameter = atof(ob->buf);
		if (ob->k == 2)
			trgb_from_split(&sp_shape->rgb, ob->spl_buf);
		if (ob->k != 1)
			free(ob->spl_buf);
		ob->k++;
	}
}

void	iter_cy(char *tmp, t_shapes *cy_shape)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		do_j_bzero(ob);
		move_cp_buf(tmp, ob);
		if (ob->k < 2 || ob->k > 3)
			ob->spl_buf = ft_split(ob->buf, ',');
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
		ob->k++;
	}
}
