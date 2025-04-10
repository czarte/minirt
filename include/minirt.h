/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:39:27 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/04 15:20:54 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_LIBRARY
#define MINIRT_LIBRARY
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "MiniRT"

#include "external.h"
#include "vec.h"


typedef struct g_list {
	char			**content;
	struct g_list	*next;
} garbage;

typedef struct s_rgb {
	float			alpha;
	int				r;
	int				g;
	int				b;
} t_rgb;

// typedef	s_cam

typedef struct s_scene {
	// t_cam			cam;
	// t_lght			lght;
	// t_ambi			ambi;
	float			a_ratio;
	int				a_rgb[3];
	float			c_xyz[3];
	int				c_rient[3];
	int				c_fov;
	float			l_xyz[3];
	float			l_bright;
	int				l_rgb[3];
} t_scene;

typedef struct d_shapes {
	char			*identifier;
	t_vec			cords;
	t_vec			axis;
	float			diameter;
	float			height;
	t_rgb			rgb;
    void			*img;
} s_shapes;

typedef struct mian_data {
	int 		argc;
	char 		**argv;
	garbage		*garbage;
	int			scenefd;
	char		**lines;
	t_list		**shapes;
	t_scene		*scene;
    int			key;
	char 		*filename;
    void		*mlx_ptr;
    void		*win_ptr;
} s_data;

/*window handing functions*/

int init_mlx_window(s_data *data);
int	key_exit(int key, void *params);
int	check_exit_button(int button,int x,int y, void *p);
int	check_mouse_button(int button,int x,int y, void *p);

/*parser*/
void	init_scene(s_data *data);

/*init*/
int	init_program(s_data *data, int argc, char **argv);

/*exit*/
void	free_data(s_data *data);

/*utils*/
int	ft_spacious(int c);

/*scene*/
void	construct_scene(s_data * data);
void	mk_scene_ambient(s_data *data, char *tmp);
void	mk_scene_camera(s_data * data, char *tmp);
void	mk_scene_light(s_data * data, char * tmp);
void	mk_obj_pl(s_data * data, char * tmp);
void	mk_obj_sp(s_data * data, char * tmp);
void	mk_obj_cy(s_data * data, char * tmp);

/*objects*/
void	init_objects(s_data * data);

/*colors*/
int	make_color(t_rgb rgb);

#endif
