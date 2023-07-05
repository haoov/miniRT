#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "gtfm.h"
# include "libft.h"
# include <stdbool.h>

# define SPHERE	0
# define PLANE	1

typedef struct s_plane
{

}t_plane;

typedef struct s_sphere
{

}t_sphere;

typedef union u_obj_type
{
	t_sphere	sphere;
	t_plane		plane;
}t_obj_type;

typedef struct s_obj
{
	t_vec		color;
	t_obj_type	type;
	bool		(*intfct)(t_ray, t_vec *, t_vec *, t_vec *, struct s_obj obj);
	t_gtfm		gtfm;
}t_obj;

typedef struct s_obj_lst
{
	t_obj				obj;
	struct s_obj_lst	*next;
}t_obj_lst;

typedef struct s_intfct
{
	bool	(*fct)(t_ray, t_vec *, t_vec *, t_vec *, struct s_obj obj);
}t_intfct;

t_obj_lst	*add_obj(t_obj_lst **obj_lst, int type);
t_obj_lst	*obj_lst_at(t_obj_lst *obj_lst, int index);

bool	sphere_intersect(t_ray ray, t_vec *p, t_vec *norm, t_vec *color, t_obj obj);
bool	plane_intersect(t_ray ray, t_vec *p, t_vec *norm, t_vec *color, t_obj obj);

bool	close_enough(double val1, double val2);

#endif //OBJECT_H
