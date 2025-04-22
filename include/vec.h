#ifndef VEC_LIBRARY
#define VEC_LIBRARY

#include "external.h"

typedef struct s_vec {
	float			x;
	float			y;
	float			z;
} t_vec;

t_vec	*new_vec(float x, float y, float z);
t_vec   vec3(float x, float y,float z);
t_vec	add(t_vec a, t_vec b);
t_vec	cross(t_vec a, t_vec b);
t_vec	scale(t_vec a, double s);
t_vec	normalize(t_vec a);
t_vec	substract(t_vec a, t_vec b);
t_vec	divide_by_scalar(t_vec a, float s);


double	vec_length(t_vec a);

#endif
