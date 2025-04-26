/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:41 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/16 16:14:41 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_imgs(void *shp)
{
	t_shapes	*shape;

	shape = (t_shapes *)shp;
	if (shape->img.mlx_ptr != NULL)
		free(shape->img.ptr);
}

void	free_data(t_data *data)
{
	char		*ltmp;

	ltmp = *data->lines;
	while (ltmp != NULL)
	{
		free(ltmp);
		data->lines++;
		ltmp = *data->lines;
	}
	//ft_lstiter(data->shapes, &free_imgs);
	ft_lstclear(&data->shapes, &free);
	free(data->shapes);
}
