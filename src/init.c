/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:52:10 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/02 23:22:14 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	check_input(t_data *data)
{
	char	*buffer;

	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
	{
		perror("Error opening file");
		exit(-1);
	}
	buffer = malloc(1);
	if (buffer == NULL)
	{
		printf("Error allocating memory\n");
		exit(-1);
	}
	if (read(data->scenefd, buffer, 1) <= 0)
	{
		printf("Error: Scene is empty\n");
		exit(-1);
	}
	close(data->scenefd);
	free(buffer);
	return ;
}

int	init_program(t_data *data, int argc, char **argv)
{
	if (argc != 2)
	{
		perror("You must provide a file name of scene");
		return (-1);
	}
	data->filename = argv[1];
	check_input(data);
	init_scene(data);
	init_objects(data);
	return (0);
}
