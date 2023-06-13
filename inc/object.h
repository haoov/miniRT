#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include <stdbool.h>

# define SPHERE	1

typedef struct s_sphere
{

}t_sphere;

typedef union u_obj_type
{
	t_sphere	sphere;
}t_obj_type;

typedef struct s_obj
{
	t_vec		color;
	t_obj_type	type;
}t_obj;

bool	sphere_intersect(t_ray ray, t_vec *p, t_vec *norm, t_vec *color);

#endif //OBJECT_H
