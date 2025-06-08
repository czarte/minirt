/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:39:27 by voparkan          #+#    #+#             */
/*   Updated: 2025/06/07 22:02:51 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_TITLE "MiniRT"
# define EPSILON 1e-6
# define READ_SUCCESS 1
# define READ_EOF 0
# define READ_ERROR -1
# define FLT_MAX 3.40282347e+38F

# include "external.h"
# include "mlx_utils.h"
# include "vec.h"

typedef struct s_ray
{
	t_vec			origin;
	t_vec			dir;
}			t_ray;

typedef struct g_list
{
	char			**content;
	struct g_list	*next;
}			t_garbage;

typedef struct s_rgb
{
	float			alpha;
	int				r;
	int				g;
	int				b;
}			t_rgb;

typedef struct s_cam
{
	t_vec			cords;
	t_vec			orient;
	t_vec			right;
	t_vec			up;
	t_vec			world_up;
	int				fov;
}				t_cam;

typedef struct s_light
{
	t_vec			cords;
	float			bright;
	t_rgb			rgb;
}			t_lght;

typedef struct s_ambient
{
	float			ratio;
	t_rgb			rgb;
}			t_ambi;

typedef struct s_scene
{
	t_cam			cam;
	t_lght			lght;
	t_ambi			ambi;
}			t_scene;

typedef struct s_img
{
	void		*ptr;
	char		*pixels;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
	void		*mlx_ptr;
}			t_img;

typedef struct s_shapes
{
	char			*identifier;
	t_vec			cords;
	t_vec			axis;
	float			diameter;
	float			height;
	t_rgb			rgb;
	t_img			img;
}	t_shapes;

typedef struct s_data
{
	int			frame;
	int			*test;
	int			argc;
	char		**argv;
	int			scenefd;
	char		**lines;
	t_list		*shapes;
	t_scene		*scene;
	int			key;
	char		*filename;
	t_img		*scene_img[2];
	void		*mlx_ptr;
	void		*win_ptr;
}				t_data;

/* bags */
typedef struct s_obag
{
	int			i;
	int			j;
	int			k;
	char		**spl_buf;
	char		buf[1024];
}			t_obag;

typedef struct s_sbag
{
	t_vec		l_dir;
	t_rgb		mix_color;
	t_rgb		diffuse;
	double		factor;
	float		softness;
	float		visibility;
}	t_sbag;

typedef struct s_rbag
{
	float		aspect;
	float		fov_radians;
	float		scale_fov;
	float		nor_x;
	float		nor_y;
}	t_rbag;

typedef struct s_spbag
{
	float		t1;
	float		t2;
	float		shp_radius;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_vec		oc;
}	t_spbag;

typedef struct s_hit_record
{
	float		t;
	t_vec		point;
	t_vec		normal;
	t_shapes	*object;
	bool		hit;
	bool		is_cap;
}	t_hit_record;

typedef struct s_cybag
{
	int				i;
	float			t1;
	float			t2;
	float			radius;
	float			a_f;
	float			b_f;
	float			c_f;
	float			discriminant;
	float			sqrt_disc;
	float			t_candidates[2];
	float			height;
	float			ti;
	float			denom;
	float			t_cap;
	float			t_body;
	float			crb;
	float			sign;
	float			half_h;
	t_vec			sub;
	t_vec			oc;
	t_vec			nor_cyl;
	t_vec			a;
	t_vec			b;
	t_vec			p;
	t_vec			p_b;
	t_vec			cap_center;
	t_vec			mul;
	t_vec			lp;
	t_hit_record	rec_body;
	t_hit_record	rec_cap;
	t_vec			to_point;
	t_vec			projection;
}	t_cybag;

typedef struct s_cap_bag
{
	t_vec	cap_center;
	t_vec	dist;
	t_vec	lp;
	t_vec	cap_normal;
	t_vec	sub;
	float	t_cap;
	float	half_h;
	float	denom;
	int		i;
	float	r2;
	float	bias;
	float	sign;
}	t_cap_bag;

typedef struct s_cap_hit_ctx
{
	t_cap_bag		*cb;
	t_cybag			*b;
	t_shapes		*shp;
	t_ray			ray;
	t_hit_record	*hit;
}	t_cap_hit_ctx;

void	do_j_bzero(t_obag *ob);
void	init_tobag(t_obag *obag);

/*window handing functions*/
int		init_mlx_window(t_data *data);
int		key_mapping(int key, void *params);
int		check_exit_button(int button, int x, int y, void *p);
int		check_mouse_button(int button, int x, int y, void *p);

/*parser*/
void	init_scene(t_data *data);
void	free_split(char **split);
void	exit_error(char *msg);

/*parser_utils*/
void	check_scene_alloc(t_data *data, void *ptr);
void	read_next_word(char *tmp, t_obag *ob);
void	print_lines(char ***tmp);
int		line_count(char *filename);

/*process_objects*/
void	process_pl(t_data *data, t_shapes *pl_shape, t_obag *ob);
void	process_sp(t_data *data, t_shapes *sp_shape, t_obag *ob);
void	process_cy(t_data *data, t_shapes *cy_shape, t_obag *ob);

/*init*/
int		init_program(t_data *data, int argc, char **argv);

/*exit*/
void	free_lines(char **lines);
void	free_data(t_data *data);
void	free_imgs(void *shp);

/*utils*/
int		ft_spacious(int c);
int		min(int a, int b);
int		max(int a, int b);
void	print_vec(t_vec a);

/*scene*/
void	construct_scene(t_data *data);
void	mk_scene_ambient(t_data *data, char *tmp);
void	mk_scene_camera(t_data *data, char *tmp);
void	mk_scene_light(t_data *data, char *tmp);
void	mk_obj_pl(t_data *data, char *tmp);
void	mk_obj_sp(t_data *data, char *tmp);
void	mk_obj_cy(t_data *data, char *tmp);
void	mrt_put_pixel(t_img *img, int x, int y, int color);
void	init_scene_img(t_data *data);

/*objects & shapes*/

void	init_objects(t_data *data);
void	print_shapes(t_list *shapes);
void	tvec_from_split(t_vec *v, char **split);
void	trgb_from_split(t_rgb *rgb, char **split);
void	iter_pl(t_data *data, char *tmp, t_shapes *pl_shape);
void	iter_sp(t_data *data, char *tmp, t_shapes *sp_shape);
void	iter_cy(t_data *data, char *tmp, t_shapes *cy_shape);
void	move_cp_buf(char *tmp, t_obag *ob);
float	process_cy_cap(t_cybag b, t_shapes *shp, t_ray ray, t_hit_record *rec);
float	process_cy_body(t_cybag b, t_shapes *shp, t_ray ray);

/*rays*/
t_ray	shoot_ray(int x, int y, t_data *data);
bool	ray_inter_sp(t_ray ray, t_shapes *shp, float *t);
bool	ray_inter_pl(t_ray ray, t_shapes *shp, float *t);
bool	ray_inter_cy(t_ray ray, t_shapes *shp, float *t, t_hit_record *rec);
void	cast_rays(t_data *data);

/*hit*/
bool	hit_objects(t_data *data, t_ray ray, t_hit_record *rec);
bool	is_in_shadow(t_data *data, t_vec point, t_vec light_pos, t_vec normal);
void	resolve_hit(t_hit_record *rec, float t, t_ray ray, t_shapes *shp);

/*colors*/
int		make_color(t_rgb rgb);
int		ray_color(t_ray ray, t_data *data);
t_rgb	shader(t_rgb color, t_data *data, t_hit_record *rec);
t_rgb	calculate_diffuse(t_data *data, t_vec dir, t_rgb color,
			t_hit_record *rec);
t_rgb	calculate_ambient(t_data *data, t_shapes *shp);
t_sbag	colors_in_shadow(t_rgb *color, t_data *data, t_hit_record *rec,
			t_sbag *sb);

/*validator*/
bool	check_line(char *line, t_obag *bag);
bool	handle_identifiers(int camera_count, int light_count,
			int ambient_count);

bool	validate_camera(char **tokens, const int count);
bool	validate_light(char **tokens, const int count);
bool	validate_ambient(char **tokens, const int count);
bool	validate_sphere(char **tokens, const int count);
bool	validate_plane(char **tokens, const int count);
bool	validate_cylindr(char **tokens, const int count);

bool	validate_rgb(const char *token);
bool	validate_orientation(const char *tokens);

void	remove_comment(char *line);

/*cy_utils*/
void	calculate_cy_bag(t_cybag *b, t_shapes *shp, t_ray ray);
void	handle_cy_body(t_cybag *b, t_shapes *shp, t_ray ray);

#endif
