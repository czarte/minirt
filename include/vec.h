#ifndef VEC_LIBRARY
#define VEC_LIBRARY

#include "external.h"

typedef struct s_vec {
    float			x;
    float			y;
    float			z;
} t_vec;

t_vec	*new_vec(float x, float y, float z);
t_vec   vec_sub(t_vec a, t_vec b);
t_vec	add(t_vec a, t_vec b);
t_vec	cross(t_vec a, t_vec b);
t_vec	scale(t_vec a, double s);
t_vec	normalize(t_vec a);
double	vec_dot(t_vec *a, t_vec *b);

double	vec_length(t_vec a);

#endif
