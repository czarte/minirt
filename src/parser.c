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

void	asign_line(char ***lines, char **line, int *i)
{
	(*line)[(*i)] = '\0';
	**lines = *line;
	*line = malloc(1024);
	bzero(*line, 1024);
	(*lines)++;
	*i = 0;
}

void	do_lines(s_data *data, char *buffer, char ***lines)
{
	char	*line;
	int		i;

	i = 0;
	line = malloc(1024);
	bzero(line, 1024);
	while (read(data->scenefd, buffer, 1) > 0)
	{
		if (strncmp(buffer, "\n", 1) == 0)
			asign_line(lines, &line, &i);
		else
			line[i++] = buffer[0];
	}
	**lines = line;
	(*lines)++;
	**lines = NULL;
}

void	print_lines(char ***tmp)
{
	while (**tmp != NULL)
	{
		printf("%s\n", **tmp);
		(*tmp)++;
	}
}

void	init_scene(s_data *data)
{
	char	*buffer;
	char	**lines;
	char	**tmp;

	buffer = malloc(1);
	lines = malloc(100 * sizeof(char *));
	tmp = lines;
	if (buffer == NULL)
	{
		printf("Error allocating memory\n");
		exit(-1);
	}
	do_lines(data, buffer, &lines);
	close(data->scenefd);
	data->lines = tmp;
	print_lines(&tmp);
	free(buffer);
}
