/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:33:32 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/21 19:40:39 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	process_line(char *line, t_obag *bag, char **lines, int *line_idx)
{
	char	*dup;

	if (!check_line(line, bag))
		return (false);
	dup = ft_strdup(line);
	if (!dup)
		return (false);
	lines[*line_idx] = dup;
	(*line_idx)++;
	return (true);
}

int	read_next_line(int fd, char *line_buf, int *i)
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
			printf("Error: line too long (max 1023 chars)\n");
			return (-1);
		}
		line_buf[(*i)++] = buffer[0];
		bytes_read = read(fd, buffer, 1);
	}
	line_buf[(*i)] = '\0';
	return (bytes_read);
}

void	cleanup_and_exit(t_data *data, char **lines, char *msg)
{
	free_lines(lines);
	free_data(data);
	exit_error(msg);
}

// bag is used here to store camera, ambient and light counts
void	do_lines(t_data *data, char **lines)
{
	char	line[1024];
	t_obag	bag;
	int		i;
	int		line_idx;
	int		read_state;

	i = 0;
	bag = (t_obag){0};
	line_idx = 0;
	while (true)
	{
		read_state = read_next_line(data->scenefd, line, &i);
		if (read_state == -1)
			cleanup_and_exit(data, lines, "Couldn't read scene");
		if (read_state == 0 && i == 0)
			break ;
		remove_comment(line);
		if (line[0] == '\0')
			continue ;
		if (!process_line(line, &bag, lines, &line_idx))
			cleanup_and_exit(data, lines, "Invalid scene line");
	}
	lines[line_idx] = NULL;
	if (!handle_identifiers(bag.i, bag.j, bag.k))
		cleanup_and_exit(data, lines, "Invalid scene line");
}

void	init_scene(t_data *data)
{
	char	**lines;
	int		lc;

	lc = line_count(data->filename);
	lines = malloc((lc + 2) * sizeof(char *));
	check_scene_alloc(data, lines);
	lines[0] = NULL;
	data->scenefd = open(data->filename, O_RDONLY);
	if (data->scenefd == -1)
	{
		free(lines);
		free_data(data);
		exit_error("Error opening file");
	}
	do_lines(data, lines);
	close(data->scenefd);
	data->lines = lines;
	print_lines(&lines);
	construct_scene(data);
}
