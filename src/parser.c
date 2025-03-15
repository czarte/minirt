/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:33:32 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/15 15:33:32 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_scene(s_data *data)
{
	char	*buffer;
	char	**lines;
	char	*line;
	char	**tmp;
	int		i;
	ssize_t	n;

	n = 0;
	i = 0;
	buffer = malloc(1);
	line = malloc(1024);
	bzero(line, 1024);
	lines = malloc(100 * sizeof(char *));
	tmp = lines;
	if (buffer == NULL)
	{
		printf("Error allocating memory\n");
		exit(-1);
	}
	while ((n = read(data->scenefd, buffer, 1)) > 0)
	{
        if (strncmp(buffer, "\n", 1) == 0) {
        	line[i] = '\0';
        	*lines = line;
        	line = malloc(1024);
        	bzero(line, 1024);
        	lines++;
        	i = 0;
        } else {
	        line[i] = buffer[0];
        	i++;
        }
	}
	*lines = line;
	data->lines = lines;
	close(data->scenefd);
	free(buffer);
}

//int	readfile(s_data *data)
//{
//
//}
