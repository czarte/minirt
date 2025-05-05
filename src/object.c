/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:38 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/05 13:46:48 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/debug.h"

void	mk_obj_pl(t_data *data, char *tmp)
{
	t_shapes	*pl_shape;
	t_list		*new;

	pl_shape = malloc(sizeof(t_shapes));
	pl_shape->identifier = "pl";
	iter_pl(tmp, pl_shape);
	pl_shape->diameter = 0;
	pl_shape->height = 0;
	new = ft_lstnew((void *) pl_shape);
	ft_lstadd_front(&data->shapes, new);
}

void	mk_obj_sp(t_data *data, char *tmp)
{
	t_shapes	*sp_shape;
	t_list		*new;

	sp_shape = malloc(sizeof(t_shapes));
	sp_shape->identifier = "sp";
	iter_sp(tmp, sp_shape);
	sp_shape->axis = (t_vec){0, 0, 0};
	sp_shape->height = 0;
	new = ft_lstnew((void *) sp_shape);
	ft_lstadd_front(&data->shapes, new);
}

void	mk_obj_cy(t_data *data, char *tmp)
{
	t_shapes	*cy_shape;
	t_list		*new;

	cy_shape = malloc(sizeof(t_shapes));
	cy_shape->identifier = "cy";
	iter_cy(tmp, cy_shape);
	new = ft_lstnew((void *) cy_shape);
	ft_lstadd_front(&data->shapes, new);
}

void	init_objects(t_data *data)
{
	char	**tmp;

	tmp = data->lines;
	data->shapes = malloc(sizeof(t_list));
	data->shapes = NULL;
	if (data->scene == NULL)
	{
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
	print_shapes(data->shapes);
}
