#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "ray.h"
# include "object.h"
# include "libft.h"
# include <stdbool.h>

typedef struct s_scene t_scene;

typedef	struct s_light
{
	t_vec	color;
	t_vec	pos;
	double	intensity;
	bool	(*illumfct)(t_vec *, t_vec *, t_vec *, double *, struct s_light *,
						t_obj *, t_obj *);
	struct s_light	*next;
}t_light;

t_light	*new_light(void);
bool	point_illum(t_vec *point, t_vec *norm, t_vec *color, double *intensity,
					t_light *light, t_obj *obj_lst, t_obj *cur_obj);

t_light	*add_light(t_light **light_lst, t_light *new);

#endif
