/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:51 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/15 15:16:22 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minirt.h"

void	init_scene(s_data *data)
{
	char	*buffer;
	ssize_t	n;

	n = 0;
	buffer = malloc(381);
	if (buffer == NULL)
	{
		printf("Error allocating memory\n");
		exit(-1);
	}
	while ((n = read(data->scenefd, buffer, 380)) > 0)
	{
		buffer[n] = '\0';
		printf("%s\n", buffer);
	}
	close(data->scenefd);
	free(buffer);
}

int	init_program(s_data *data, int argc, char **argv)
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
	return (0);
}

int	main(int argc, char *argv[])
{
	s_data	*data;

	data = malloc(sizeof(s_data));
	if (data == NULL)
		return (-1);
	if (init_program(data, argc, argv) == -1)
		exit(-1);
	if (init_mlx_window(data) == -1)
		exit(-1);
	mlx_key_hook(data->win_ptr, &key_exit, (void *)data);
	mlx_mouse_hook(data->win_ptr, &check_mouse_button, (void *)data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &mlx_loop_end, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data);
	exit(0);
	return (0);
}
