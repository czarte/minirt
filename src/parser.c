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

//int	readfile(s_data *data)
//{
//
//}
