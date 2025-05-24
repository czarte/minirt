/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:47 by voparkan          #+#    #+#             */
/*   Updated: 2025/05/10 13:42:58 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

//void	to_left(void *shp)
//{
//	t_shapes	*shape;
//
//	shape = (t_shapes *)shp;
//	shape->cords.x += 1;
//}
//
//void	to_right(void *shp)
//{
//	t_shapes	*shape;
//
//	shape = (t_shapes *)shp;
//	shape->cords.x -= 1;
//}
//
//void	to_top(void *shp)
//{
//	t_shapes	*shape;
//
//	shape = (t_shapes *)shp;
//	shape->cords.y -= 1;
//}
//
//void	to_bottom(void *shp)
//{
//	t_shapes	*shape;
//
//	shape = (t_shapes *)shp;
//	shape->cords.y += 1;
//}
//
//void	to_forw(void *shp)
//{
//	t_shapes	*shape;
//
//	shape = (t_shapes *)shp;
//	shape->cords.z += 1;
//}
//
//void	to_back(void *shp)
//{
//	t_shapes	*shape;
//
//	shape = (t_shapes *)shp;
//	shape->cords.z -= 1;
//}
//
//void    resolve_light_move(t_data *data, int key, bool *cast)
//{
//	if (key == L_KEY_A_L || key == L_KEY_D_R || key == L_KEY_S_B ||
//        	key == L_KEY_W_U)
//		*cast = true;
//	if (key == L_KEY_A_L) //light left
//		data->scene->lght.cords.x -= 1;
//	if (key == L_KEY_D_R) //light right
//		data->scene->lght.cords.x += 1;
//	if (key == L_KEY_S_B) //light bottom
//		data->scene->lght.cords.y -= 1;
//	if (key == L_KEY_W_U) //light top
//		data->scene->lght.cords.y += 1;
//}
//
//void    resolve_camera_move(t_data *data, int key, bool *cast)
//{
//	if (key == C_KEY_UP || key == C_KEY_DOWN || key == C_KEY_LEFT ||
//        	key == C_KEY_RIGHT || key == 61 || key == 45)
//		*cast = true;
//	if (key == C_KEY_UP) //camera forward
//		data->scene->cam.cords.y += 1;
//	if (key == C_KEY_DOWN) //camera backward
//		data->scene->cam.cords.y -= 1;
//	if (key == C_KEY_LEFT) //camera forward
//		data->scene->cam.cords.x -= 1;
//	if (key == C_KEY_RIGHT) //camera backward
//		data->scene->cam.cords.x += 1;
//	if (key == 61) //camera forward
//		data->scene->cam.cords.z -= 1;
//	if (key == 45) //camera backward
//		data->scene->cam.cords.z += 1;
//}
//
//void    resolve_object_move(t_data *data, int key, bool *cast)
//{
//	if (key == O_KEY_A_L || key == O_KEY_W_U || key == O_KEY_D_R ||
//        	key == O_KEY_S_B)
//		*cast = true;
//	if (key == O_KEY_A_L)
//		ft_lstiter(data->shapes, &to_left);
//	if (key == O_KEY_W_U)
//		ft_lstiter(data->shapes, &to_top);
//	if (key == O_KEY_D_R)
//		ft_lstiter(data->shapes, &to_right);
//	if (key == O_KEY_S_B)
//		ft_lstiter(data->shapes, &to_bottom);
//}

/*
 * moves that could be part of key mapping functions
 *
 	bool    cast = false;

 	printf("Keys in miniRT : %d\n", key);
	data->frame++;
    resolve_light_move(data, key, &cast);
    resolve_camera_move(data, key, &cast);
    resolve_object_move(data, key, &cast);
    if (key == A_KEY_DWN && (data->scene->ambi.ratio >= 0.1f &&
            data->scene->ambi.ratio <= 1.0)) {
        data->scene->ambi.ratio -= 0.1f;
        cast = true;
    } else if (key == A_KEY_UP && (data->scene->ambi.ratio <= 0.9f &&
        data->scene->ambi.ratio >= 0.0f)) {
        data->scene->ambi.ratio += 0.1f;
        cast = true;
    }
    if (cast)
    {
        cast_rays(data);
        mlx_destroy_image(data->mlx_ptr, data->scene_img[frame_n]->ptr);
    }
 *
 * */