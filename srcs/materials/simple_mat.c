#include "material.h"

t_material	simple_mat_const(t_vec color, double ref, double shiny)
{
	t_material	mat;

	mat.color = color;
	mat.reflec = ref;
	mat.shiny = shiny;
	mat.max_ref_ray = 3;
	mat.ref_ray_count = 0;
	mat.has_texture = false;
	mat.colorfct = spl_compute_color;
	mat.ambiant_color = vec_create(1.0, 1.0, 1.0);
	mat.ambiant_intensity = 0.2;
	return (mat);
}

t_vec	spl_compute_color(t_obj_lst *obj_lst, t_light_lst *light_lst, t_poi poi,
					   t_ray cam_ray, t_material mat)
{
	//Define the initials materials colors
	t_vec	mat_color = vec_create(0.0, 0.0, 0.0);
	t_vec	ref_color = vec_create(0.0, 0.0, 0.0);
	t_vec	dif_color = vec_create(0.0, 0.0, 0.0);
	t_vec	spec_color = vec_create(0.0, 0.0, 0.0);
	(void)ref_color;

	//Compute the diffuse component
	if (!poi.obj->material.has_texture)
		dif_color = compute_diffuse_color(obj_lst, light_lst, poi,
										  poi.obj->material.color);
	else
		dif_color = compute_diffuse_color(obj_lst, light_lst, poi,
										  poi.obj->material.texture.colorfct(
												  poi.obj->material.texture,
												  poi.u, poi.v));

	//Compute the reflection color
	if (mat.reflec)
	{
		ref_color = compute_ref_color(obj_lst, light_lst, poi, cam_ray, poi.obj->material);
	}

	//Combine reflection and diffuse component
	mat_color = vec_add(vec_mult(ref_color, mat.reflec), vec_mult(dif_color, 1.0 - mat.reflec));

	//Compute the specular component
	if (mat.shiny > 0.0)
	{
		spec_color = compute_spec_color(obj_lst, light_lst, poi, cam_ray, poi.obj->material);
	}

	//Add the spec to the final color
	mat_color = vec_add(mat_color, spec_color);

	return (mat_color);
}
