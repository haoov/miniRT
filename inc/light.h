#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "ray.h"
# include "object.h"

# define POINT	1

typedef struct s_light
{
	t_vec	color;
	t_vec	pos;
	double	intensity;
	bool	(*illumfct)(t_vec *, t_vec *, t_vec *, double *, struct s_light,
			t_obj_lst *, t_obj_lst *);
}t_light;

typedef	struct s_light_lst
{
	t_light				light;
	struct s_light_lst	*next;
}t_light_lst;

bool	point_illum(t_vec *point, t_vec *norm, t_vec *color, double *intensity,
					t_light light, t_obj_lst *obj_lst, t_obj_lst *cur_obj);

t_light_lst	*add_light(t_light_lst **light_lst, int type);
t_light_lst	*light_lst_at(t_light_lst *ligt_lst, int index);

#endif
