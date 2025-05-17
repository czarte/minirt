/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:52:10 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/17 18:31:53 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	check_file_empty(t_data *data)
{
	char	*buffer;

	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	buffer = malloc(1);
	check_scene_alloc(data, buffer);
	if (read(data->scenefd, buffer, 1) <= 0)
	{
		printf("Error: Scene is empty\n");
		exit(EXIT_FAILURE);
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
	check_file_empty(data);
	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
    data->frame = 1;
    data->test = malloc(sizeof(int));
    *data->test = 0;
    data->scene_img[0] = malloc(sizeof(t_img));
    data->scene_img[1] = malloc(sizeof(t_img));
	init_scene(data);
	init_objects(data);
    printf("INIT data->frame: %d\n", data->frame);
	return (0);
}
