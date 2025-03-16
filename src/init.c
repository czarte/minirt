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

void create_scene_a(s_data *data, char *tmp)
{
	int		i;
	int		j;
	char	buf[1024];

	i = 1;
	j = 0;
	bzero(buf, 1024);
	while (ft_spacious(tmp[i]))
		i++;
	while (!ft_spacious(tmp[i]))
		buf[j++] = tmp[i++];
	tmp[i] = '\0';
	data->scene->a_ratio = atof(buf);
}

void	construct_scene(s_data * data)
{
	char	**tmp;

	tmp = data->lines;
	data->scene = malloc(sizeof(s_scene));
	if (data->scene == NULL) {
		perror("Error allocating memory for scene");
		exit(-1);
	}
	while (*tmp)
	{
		if (*tmp[0] == 'A')
			create_scene_a(data, *tmp);
		tmp++;
	}
}
