#ifndef MATERIAL_H
# define MATERIAL_H

# include "vector.h"
# include "ray.h"
# include "light.h"

# define NONE	0
# define SIMPLE 1

t_material	simple_mat_const(t_vec color, double ref, double shiny);

void	assign_material(t_obj_lst *obj, t_material material);

t_vec	spl_compute_color(t_obj_lst *obj_lst, t_light_lst *light_lst, t_poi poi,
						   t_ray cam_ray, t_material mat);
t_vec	compute_diffuse_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
							   t_poi poi, t_vec base_color);
t_vec	compute_ref_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
						   t_poi poi, t_ray incident_ray, t_material mat);

#endif
