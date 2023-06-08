#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}t_vec;

t_vec	vec_create(double x, double y, double z);
t_vec	vec_sub(t_vec vec1, t_vec vec2);
t_vec	vec_add(t_vec vec1, t_vec vec2);
t_vec	vec_mult(t_vec vec, double scalar);
t_vec	vec_cross(t_vec vec1, t_vec vec2);
double	vec_norm(t_vec vec);
double	vec_dot(t_vec vec1, t_vec vec2);
void	vec_normalize(t_vec *vec);

#endif //VECTOR_H
