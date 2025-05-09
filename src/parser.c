/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:33:32 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/09 13:40:51 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	process_line(char *line, t_obag *bag, char ***lines)
{
	char	*dup;

	if (!check_line(line, bag))
		return (false);
	dup = ft_strdup(line);
	if (!dup)
		return (false);
	**lines = dup;
	if (!**lines)
		return (false);
	(*lines)++;
	return (true);
}

bool	read_next_line(int fd, char *line_buf, int *i)
{
	char	buffer[1];
	int		bytes_read;

	*i = 0;
	bytes_read = read(fd, buffer, 1);
	while (bytes_read > 0)
	{
		if (buffer[0] == '\n')
			break ;
		if (*i >= 1023)
		{
			line_buf[1023] = '\0';
			return (true);
		}
		line_buf[(*i)++] = buffer[0];
		bytes_read = read(fd, buffer, 1);
		if (bytes_read < 0)
		{
			perror("Read failed");
			return (false);
		}
	}
	line_buf[(*i)] = '\0';
	return (bytes_read != 0 || *i > 0);
}

// bag is used here to store camera, ambient and light counts
void	do_lines(t_data *data, char ***lines)
{
	char	line[1024];
	t_obag	bag;
	int		i;
	char	**current;

	i = 0;
	bag = (t_obag){0, 0, 0, NULL};
	current = *lines;
	while (read_next_line(data->scenefd, line, &i))
	{
		if (i == 0)
			continue ;
		if (!process_line(line, &bag, &current))
		{
			free_lines(*lines);
			exit_error("Invalid scene line");
		}
	}
	if (!handle_identifiers(bag.i, bag.j, bag.k))
	{
		free_lines(*lines);
		exit_error("Invalid scene line");
	}
	*current = NULL;
}

void	print_lines(char ***tmp)
{
	while (**tmp != NULL)
	{
		printf("%s\n", **tmp);
		(*tmp)++;
	}
}

void	init_scene(t_data *data)
{
	char	**lines;
	char	**tmp;

	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
		exit_error("Error opening file");
	lines = malloc(100 * sizeof(char *));
	if (!lines)
		perror("Failed to allocate memory in init_scene");
	tmp = lines;
	do_lines(data, &lines);
	close(data->scenefd);
	data->lines = tmp;
	print_lines(&tmp);
	construct_scene(data);
}
