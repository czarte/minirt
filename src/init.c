/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:52:10 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/22 17:19:54 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	check_filename(t_data *data)
{
	char	*filename;

	filename = data->filename;
	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3))
	{
		perror("Error opening file: wrong format");
		free(data);
		exit(EXIT_FAILURE);
	}
}

void	check_file_empty(t_data *data)
{
	char	*buffer;

	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
	{
		perror("Error opening file");
		free(data);
		exit(EXIT_FAILURE);
	}
	buffer = malloc(1);
	check_scene_alloc(data, buffer);
	if (read(data->scenefd, buffer, 1) <= 0)
	{
		printf("Error: Scene is empty\n");
		free(buffer);
		free(data);
		exit(EXIT_FAILURE);
	}
	close(data->scenefd);
	free(buffer);
}

int	init_program(t_data *data, int argc, char **argv)
{
	if (argc != 2)
	{
		perror("You must provide a file name of scene");
		return (-1);
	}
	data->filename = argv[1];
	data->frame = 1;
	check_filename(data);
	check_file_empty(data);
	init_scene(data);
	data->scene_img[0] = malloc(sizeof(t_img));
	data->scene_img[1] = malloc(sizeof(t_img));
	init_objects(data);
	printf("INIT data->frame: %d\n", data->frame);
	return (0);
}
