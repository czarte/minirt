/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:58:54 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/17 20:43:09 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	read_next_word(char *tmp, t_obag *ob)
{
	do_j_bzero(ob);
	while (ft_spacious(tmp[ob->i]))
		ob->i++;
	while (tmp[ob->i] && !ft_spacious(tmp[ob->i]))
		ob->buf[ob->j++] = tmp[ob->i++];
	ob->buf[ob->j] = '\0';
}

void	check_scene_alloc(t_data *data, void *ptr)
{
	if (!ptr)
	{
		free_data(data);
		exit_error("Error: failed to allocate memory");
	}
}

void	print_lines(char ***tmp)
{
	while (**tmp != NULL)
	{
		printf("%s\n", **tmp);
		(*tmp)++;
	}
}

int	line_count(char *filename)
{
	char	buffer[1];
	int		fd;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Error opening file");
	while (read(fd, buffer, 1))
	{
		if (buffer[0] == '\n')
			count++;
	}
	close(fd);
	return (count);
}
