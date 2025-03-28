/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:38 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/28 14:23:38 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void mk_obj_pl(s_data * data, char * tmp) {
	(void) data;
	(void) tmp;
	printf("pl\n");
}

void mk_obj_sp(s_data * data, char * tmp) {
	int			i;
	int			j;
	int			k;
	s_shapes	*sp_shape;
	t_list		*new;
	char		buf[1024];
	char		**spl_buf;

	k = 0;
	i = 1;
	spl_buf = NULL;
	sp_shape = malloc(sizeof(s_shapes));
	sp_shape->identifier = "sp";
	while (tmp[i] != '\0')
	{
		j = 0;
		printf("sp: %s\n", tmp);
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
			// printf("spl_buf %s\n", spl_buf[0]);
			// printf("spl_buf %s\n", spl_buf[1]);
			// printf("spl_buf %s\n", spl_buf[2]);
			// sp_shape->cords = malloc(sizeof(t_vec));
			sp_shape->cords.x = atof(spl_buf[0]);
			sp_shape->cords.y = atof(spl_buf[1]);
			sp_shape->cords.z = atof(spl_buf[2]);
			while (j < 3) {
				free(spl_buf[j]);
				j++;
			}
		}
		if (k == 1)
			sp_shape->diameter = atof(buf);
		if (k == 2) {
			sp_shape->rgb = (t_rgb) { 1, ft_atoi(spl_buf[0]), ft_atoi(spl_buf[1]), ft_atoi(spl_buf[2]) };
			while (j < 3) {
				free(spl_buf[j]);
				j++;
			}
		}
		if (k != 1)
			free(spl_buf);
		k++;
	}
	sp_shape->axis = (t_vec) { 0, 0, 0 };
	sp_shape->height = 0;
	new = ft_lstnew((void *) sp_shape);
	ft_lstadd_front(data->shapes, new);
}

void mk_obj_cy(s_data *data, char *tmp) {
	int			i;
	int			j;
	int			k;
	s_shapes	*cy_shape;
	t_list		*new;
	char		buf[1024];
	char		**spl_buf;

	k = 0;
	i = 1;
	spl_buf = NULL;
	cy_shape = malloc(sizeof(s_shapes));
	cy_shape->identifier = "cy";
	while (tmp[i] != '\0')
	{
		j = 0;
		bzero(buf, 1024);
		while (ft_spacious(tmp[i]))
			i++;
		while (tmp[i] && !ft_spacious(tmp[i]))
			buf[j++] = tmp[i++];
		buf[i] = '\0';
		if (k < 2 || k > 3)
			spl_buf = ft_split(buf, ',');
		j = 0;
		if (k == 0) {
			cy_shape->cords.x = atof(spl_buf[0]);
			cy_shape->cords.y = atof(spl_buf[1]);
			cy_shape->cords.z = atof(spl_buf[2]);
			//cy_shape->cords = &(t_vec) { atof(spl_buf[0]), atof(spl_buf[1]), atof(spl_buf[2]) };
			while (j < 3) {
				free(spl_buf[j]);
				j++;
			}
		}
		if (k == 1) {
			cy_shape->axis = (t_vec) { atof(spl_buf[0]), atof(spl_buf[1]), atof(spl_buf[2]) };
			while (j < 3) {
				free(spl_buf[j]);
				j++;
			}
		}
		if (k == 2)
			cy_shape->diameter = atof(buf);
		if (k == 3)
			cy_shape->height = atof(buf);
		if (k == 4) {
			cy_shape->rgb = (t_rgb) { 1, ft_atoi(spl_buf[0]), ft_atoi(spl_buf[1]), ft_atoi(spl_buf[2]) };
			while (j < 3) {
				free(spl_buf[j]);
				j++;
			}
		}
		if (k < 2 || k > 3)
			free(spl_buf);
		k++;
	}
	new = ft_lstnew((void *) cy_shape);
	ft_lstadd_front(data->shapes, new);
}

void init_objects(s_data *data) {
	char	**tmp;

	tmp = data->lines;
	data->shapes = malloc(sizeof(t_list **));
	*data->shapes = NULL;
	if (data->scene == NULL) {
		perror("Error allocating memory for scene");
		exit(-1);
	}
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "pl ", 3) == 0)
			mk_obj_pl(data, (*tmp + 2));
		if (ft_strncmp(*tmp, "sp ", 3) == 0)
			mk_obj_sp(data, (*tmp + 2));
		if (ft_strncmp(*tmp, "cy ", 3) == 0)
			mk_obj_cy(data, (*tmp + 2));
		tmp++;
	}
	t_list **temp = data->shapes;
	while (*temp != NULL) {
		s_shapes *shp = (s_shapes *) (*temp)->content;
		printf("--------\n%s \ncoords:\t%.1f %.1f %.1f; \naxis:\t%.1f %.1f %.1f;\nd:\t\t%.1f;\th: %.1f;\nrgb:\t[%d, %d, %d] \n",
			shp->identifier, shp->cords.x, shp->cords.y, shp->cords.z,
			shp->axis.x, shp->axis.y, shp->axis.z, shp->diameter, shp->height,
			shp->rgb.r, shp->rgb.g, shp->rgb.b);
		temp = &(*temp)->next;
	}
}
