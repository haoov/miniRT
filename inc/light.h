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
	struct s_light	*next;
}t_light;

t_light	*new_light(void);
t_light	*add_light(t_light **light_lst, t_light *new);
bool	point_illum(t_scene scene, t_poi *poi, t_light light);

#endif
