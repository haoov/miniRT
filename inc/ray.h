#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct s_ray
{
	t_vec	pa;
	t_vec	pb;
	t_vec	ab;
}t_ray;

t_ray	ray_create(t_vec start, t_vec point);

#endif //RAY_H
