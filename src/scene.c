/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:44:17 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/21 18:22:30 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/debug.h"

void	mk_scene_ambient(t_data *data, char *tmp)
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
	data->scene->ambi.ratio = ft_atof(buf);
	bzero(buf, 1024);
	j = 0;
	while (ft_spacious(tmp[i]))
		i++;
	while (tmp[i] != '\0' && !ft_spacious(tmp[i]))
		buf[j++] = tmp[i++];
	buf[j] = '\0';
	spl_buf = ft_split(buf, ',');
	check_scene_alloc(data, spl_buf);
	trgb_from_split(&data->scene->ambi.rgb, spl_buf);
	free(spl_buf);
}

static void	set_camera_vectors(t_cam *cam)
{
	t_vec	world_up;

	world_up = (t_vec){0.0, 1.0, 0.0};
	cam->right = normalize(cross(cam->orient, world_up));
	cam->up = cross(cam->right, cam->orient);
}

void	mk_scene_camera(t_data *data, char *tmp)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	check_scene_alloc(data, ob);
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		read_next_word(tmp, ob);
		if (ob->k < 2)
		{
			ob->spl_buf = ft_split(ob->buf, ',');
			check_scene_alloc(data, ob->spl_buf);
		}
		if (ob->k == 0)
			tvec_from_split(&data->scene->cam.cords, ob->spl_buf);
		if (ob->k == 1)
			tvec_from_split(&data->scene->cam.orient, ob->spl_buf);
		if (ob->k == 2)
			data->scene->cam.fov = ft_atoi(ob->buf);
		if (ob->k < 2)
			free(ob->spl_buf);
		ob->k++;
	}
	set_camera_vectors(&data->scene->cam);
	free(ob);
}

void	mk_scene_light(t_data *data, char *tmp)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	check_scene_alloc(data, ob);
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		read_next_word(tmp, ob);
		if (ob->k != 1)
		{
			ob->spl_buf = ft_split(ob->buf, ',');
			check_scene_alloc(data, ob->spl_buf);
		}
		if (ob->k == 0)
			tvec_from_split(&data->scene->lght.cords, ob->spl_buf);
		if (ob->k == 1)
			data->scene->lght.bright = ft_atof(ob->buf);
		if (ob->k == 2)
			trgb_from_split(&data->scene->lght.rgb, ob->spl_buf);
		if (ob->k != 1)
			free(ob->spl_buf);
		ob->k++;
	}
	free(ob);
}

void	construct_scene(t_data *data)
{
	char	**tmp;

	tmp = data->lines;
	data->scene = malloc(sizeof(t_scene));
	check_scene_alloc(data, data->scene);
	memset(data->scene, 0, sizeof(t_scene));
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
	print_scene(data);
}
