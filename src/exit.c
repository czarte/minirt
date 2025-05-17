/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:41 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/11 16:40:18 by aevstign         ###   ########.fr       */
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


void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i])
			free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_data(t_data *data)
{
	free_lines(data->lines);
	ft_lstclear(&data->shapes, &free);
	free(data->shapes);
	if (data->scene)
		free(data->scene);
}
