#ifndef MATERIAL_H
# define MATERIAL_H

# include "vector.h"
# include "ray.h"
# include "light.h"

# define NONE	0
# define SIMPLE 1

t_material	simple_mat_const(t_vec color, double ref, double shiny);
t_material	refractive_mat_const(t_vec color, double ref, double shiny,
								   double trans);

void	assign_mat(t_obj *obj, t_material material);
void	assign_nmap(t_material *mat, t_normal_map map);

t_vec	spl_compute_color(t_scene scene, t_ray in_ray, t_poi poi);
t_vec	ref_compute_color(t_scene scene, t_ray in_ray, t_poi poi);

t_vec	diff_color(t_scene scene, t_poi poi, t_vec b_color);
t_vec	ref_color(t_scene scene, t_ray in_ray, t_poi poi);
t_vec	spec_color(t_scene scene, t_ray in_ray, t_poi poi);
t_vec	compute_ref_diff(t_scene scene, t_ray in_ray, t_poi poi);

bool	cast_ray(t_ray cast_ray, t_poi *poi, t_obj *obj_lst,
				 t_obj *obj_cur);

#endif
