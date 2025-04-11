/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:52:10 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/16 15:52:28 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_program(t_data *data, int argc, char **argv)
{
	if (argc != 2)
	{
		perror("You must provide a file name of scene");
		return (-1);
	}
	data->filename = argv[1];
	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	init_scene(data);
	init_objects(data);
	return (0);
}
