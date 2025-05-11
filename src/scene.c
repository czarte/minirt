/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:44:17 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/10 20:42:02 by aevstign         ###   ########.fr       */
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
	data->scene->ambi.ratio = atof(buf);
	bzero(buf, 1024);
	j = 0;
	while (ft_spacious(tmp[i]))
		i++;
	while (tmp[i] != '\0' && !ft_spacious(tmp[i]))
		buf[j++] = tmp[i++];
	buf[i] = '\0';
	spl_buf = ft_split(buf, ',');
	trgb_from_split(&data->scene->ambi.rgb, spl_buf);
	free(spl_buf);
}

void	mk_scene_camera(t_data *data, char *tmp)
{
	t_obag	*ob;
	t_vec	*world_up;

	ob = malloc(sizeof(t_obag));
	init_tobag(ob);
	world_up = new_vec(0.0, 1.0, 0.0);
	while (tmp[ob->i] != '\0')
	{
		do_j_bzero(ob);
		while (ft_spacious(tmp[ob->i]))
			ob->i++;
		while (tmp[ob->i] && !ft_spacious(tmp[ob->i]))
			ob->buf[ob->j++] = tmp[ob->i++];
		ob->buf[ob->i] = '\0';
		if (ob->k < 2)
			ob->spl_buf = ft_split(ob->buf, ',');
		if (ob->k == 0)
			tvec_from_split(&data->scene->cam.cords, ob->spl_buf);
		if (ob->k == 1)
			tvec_from_split(&data->scene->cam.orient, ob->spl_buf);
		if (ob->k == 2)
			data->scene->cam.fov = ft_atoi(ob->buf);
		if (ob->k < 2)
			free(ob->spl_buf);
		if (fabs(vec_dot(&data->scene->cam.orient, world_up)) > 0.999)
		{
			world_up->x = 0.0;
			world_up->y = 0.0;
			world_up->z = 1.0;
		}
		ob->k++;
	}
	free(ob);
}

void	mk_scene_light(t_data *data, char *tmp)
{
	t_obag	*ob;

	ob = malloc(sizeof(t_obag));
	init_tobag(ob);
	while (tmp[ob->i] != '\0')
	{
		do_j_bzero(ob);
		while (ft_spacious(tmp[ob->i]))
			ob->i++;
		while (tmp[ob->i] && !ft_spacious(tmp[ob->i]))
			ob->buf[ob->j++] = tmp[ob->i++];
		ob->buf[ob->i] = '\0';
		if (ob->k != 1)
			ob->spl_buf = ft_split(ob->buf, ',');
		if (ob->k == 0)
			tvec_from_split(&data->scene->lght.cords, ob->spl_buf);
		if (ob->k == 1)
			data->scene->lght.bright = atof(ob->buf);
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
	if (data->scene == NULL)
	{
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
	print_scene(data);
}
