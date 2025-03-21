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

void mk_scene_ambient(s_data *data, char *tmp)
{
	int		i;
	int		j;
	char	buf[1024];
	char	**spl_buf;

	i = 1;
	j = 0;
	bzero(buf, 1024);
	while (ft_spacious(tmp[i]))
		i++;
	while (!ft_spacious(tmp[i]))
		buf[j++] = tmp[i++];
	buf[i] = '\0';
	data->scene->a_ratio = atof(buf);
	bzero(buf, 1024);
	j = 0;
	while (ft_spacious(tmp[i]))
		i++;
	while (tmp[i] != '\0' && !ft_spacious(tmp[i]))
		buf[j++] = tmp[i++];
	buf[i] = '\0';
	spl_buf = ft_split(buf, ',');
	j = 0;
	while (j < 3) {
		data->scene->a_rgb[j] = ft_atoi(spl_buf[j]);
		free(spl_buf[j]);
		j++;
	}
	free(spl_buf);
}

void mk_scene_camera(s_data * data, char *tmp)
{
	int		i;
	int		j;
	int		k;
	char	buf[1024];
	char	**spl_buf;

	k = 0;
	i = 1;
	while (tmp[i] != '\0')
	{
		j = 0;
		bzero(buf, 1024);
		while (ft_spacious(tmp[i]))
			i++;
		while (tmp[i] && !ft_spacious(tmp[i]))
			buf[j++] = tmp[i++];
		buf[i] = '\0';
		if (k < 2)
			spl_buf = ft_split(buf, ',');
		j = 0;
		if (k == 0) {
			while (j < 3) {
				data->scene->c_xyz[j] = atof(spl_buf[j]);
				free(spl_buf[j]);
				j++;
			}
		}
		if (k == 1) {
			while (j < 3) {
				data->scene->c_rient[j]	 = ft_atoi(spl_buf[j]);
				free(spl_buf[j]);
				j++;
			}
		}
		if (k == 2)
			data->scene->c_fov = ft_atoi(buf);
		if (k < 2)
			free(spl_buf);
		k++;
	}
}

void mk_scene_light(s_data * data, char * tmp) {
	int		i;
	int		j;
	int		k;
	char	buf[1024];
	char	**spl_buf;

	k = 0;
	i = 1;
	while (tmp[i] != '\0')
	{
		j = 0;
		bzero(buf, 1024);
		while (ft_spacious(tmp[i]))
			i++;
		while (tmp[i] && !ft_spacious(tmp[i]))
			buf[j++] = tmp[i++];
		buf[i] = '\0';
		if (k != 1)
			spl_buf = ft_split(buf, ',');
		j = 0;
		if (k == 0) {
			while (j < 3) {
				data->scene->l_xyz[j] = atof(spl_buf[j]);
				free(spl_buf[j]);
				j++;
			}
		}
		if (k == 1)
			data->scene->l_bright = atof(buf);
		if (k == 2) {
			while (j < 3) {
				data->scene->l_rgb[j]	 = ft_atoi(spl_buf[j]);
				free(spl_buf[j]);
				j++;
			}
		}
		if (k != 1)
			free(spl_buf);
		k++;
	}
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
			mk_scene_ambient(data, *tmp);
		if (*tmp[0] == 'C')
			mk_scene_camera(data, *tmp);
		if (*tmp[0] == 'L')
			mk_scene_light(data, *tmp);
		tmp++;
	}
	printf("scene>\na_ratio:\t %.1f\n", data->scene->a_ratio);
	printf("a_rgb:\t\t [%d,%d,%d]\n", data->scene->a_rgb[0], data->scene->a_rgb[1], data->scene->a_rgb[2]);
	printf("c_rient:\t [%d,%d,%d]\n", data->scene->c_rient[0], data->scene->c_rient[1], data->scene->c_rient[2]);
	printf("c_xyz:\t\t [%.1f,%.1f,%.1f]\n", data->scene->c_xyz[0], data->scene->c_xyz[1], data->scene->c_xyz[2]);
	printf("c_fov:\t\t %d\n", data->scene->c_fov);
	printf("l_xyz:\t\t [%.1f,%.1f,%.1f]\n", data->scene->l_xyz[0], data->scene->l_xyz[1], data->scene->l_xyz[2]);
	printf("l_bright:\t %.1f\n", data->scene->l_bright);
	printf("l_rgb:\t\t [%d,%d,%d]\n", data->scene->a_rgb[0], data->scene->a_rgb[1], data->scene->a_rgb[2]);
}
