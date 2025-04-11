/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:39:27 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/11 15:00:04 by voparkan         ###   ########.fr       */
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

typedef struct s_img {
	void		*ptr;
	char		*pixels;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
	void		*mlx_ptr;
} t_img;

typedef struct s_shapes {
	char			*identifier;
	t_vec			cords;
	t_vec			axis;
	float			diameter;
	float			height;
	t_rgb			rgb;
    t_img			img;
} t_shapes;

typedef struct s_data {
	int 		argc;
	char 		**argv;
	garbage		*garbage;
	int			scenefd;
	char		**lines;
	t_list		*shapes;
	t_scene		*scene;
    int			key;
	char 		*filename;
    void		*mlx_ptr;
    void		*win_ptr;
} t_data;

/* bags */
typedef struct s_obag {
	int			i;
	int			j;
	int			k;
	char		**spl_buf;
	char		buf[1024];
} t_obag;

void	do_j_bzero(t_obag *ob);
void	init_tobag(t_obag *obag);


/*window handing functions*/
int init_mlx_window(t_data *data);
int	key_exit(int key, void *params);
int	check_exit_button(int button,int x,int y, void *p);
int	check_mouse_button(int button,int x,int y, void *p);

/*parser*/
void	init_scene(t_data *data);

/*init*/
int	init_program(t_data *data, int argc, char **argv);

/*exit*/
void	free_data(t_data *data);
void	free_imgs(void *shp);

/*utils*/
int	ft_spacious(int c);

/*scene*/
void	construct_scene(t_data * data);
void	mk_scene_ambient(t_data *data, char *tmp);
void	mk_scene_camera(t_data * data, char *tmp);
void	mk_scene_light(t_data * data, char * tmp);
void	mk_obj_pl(t_data * data, char * tmp);
void	mk_obj_sp(t_data * data, char * tmp);
void	mk_obj_cy(t_data * data, char * tmp);

/*objects & shapes*/

void	init_objects(t_data *data);
void	print_shapes(t_list *shapes);
void	tvec_from_split(t_vec *v, char **split);
void	trgb_from_split(t_rgb *rgb, char **split);
void	iter_pl(char *tmp, t_shapes *pl_shape);
void	iter_sp(char *tmp, t_shapes *sp_shape);
void	iter_cy(char *tmp, t_shapes *cy_shape);
void	move_cp_buf(char *tmp, t_obag *ob);

/*colors*/
int	make_color(t_rgb rgb);

#endif
