#include "vector.h"


#include <stdio.h>
void	vec_print(t_vec vec)
{
	printf("x = %f\n", vec.x);
	printf("y = %f\n", vec.y);
	printf("z = %f\n\n", vec.z);
}

t_vec	vec_create(double x, double y, double z)
{
	t_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vec4	vec4_create(double x, double y, double z, double w)
{
	t_vec4	vec4;

	vec4.x = x;
	vec4.y = y;
	vec4.z = z;
	vec4.w = w;
	return (vec4);
}

double	vec_norm(t_vec vec)
{
	double	res;

	res = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (res);
}

t_vec	vec_sub(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.x - vec2.x;
	new_vec.y = vec1.y - vec2.y;
	new_vec.z = vec1.z - vec2.z;
	return (new_vec);
}

t_vec	vec_add(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.x + vec2.x;
	new_vec.y = vec1.y + vec2.y;
	new_vec.z = vec1.z + vec2.z;
	return (new_vec);
}

t_vec	vec_mult(t_vec vec, double scalar)
{
	t_vec	new_vec;

	new_vec.x = vec.x * scalar;
	new_vec.y = vec.y * scalar;
	new_vec.z = vec.z * scalar;
	return (new_vec);
}

double	vec_dot(t_vec vec1, t_vec vec2)
{
	double	res;

	res = vec1.x * vec2.x;
	res += vec1.y * vec2.y;
	res += vec1.z * vec2.z;
	return (res);
}

t_vec	vec_cross(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
	new_vec.y = -((vec1.x * vec2.z) - (vec1.z * vec2.x));
	new_vec.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));
	return (new_vec);
}

void	vec_normalize(t_vec *vec)
{
	double	norm;

	norm = vec_norm(*vec);
	*vec = vec_mult(*vec, 1 / norm);
}

t_vec	vec_normalized(t_vec vec)
{
	double	norm;
	t_vec	res;

	norm = vec_norm(vec);
	res = vec_mult(vec, 1 / norm);
	return (res);
}
