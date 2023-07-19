#include "material.h"
#include "scene.h"

t_material	simple_mat_const(t_vec color, double ref, double shiny)
{
	t_material	mat;

	ft_memset(&mat, 0, sizeof (t_material));
	mat.color = color;
	mat.reflec = ref;
	mat.shiny = shiny;
	mat.max_ref_ray = 3;
	mat.ref_ray_count = 0;
	mat.has_texture = false;
	mat.has_nmap = false;
	mat.colorfct = spl_compute_color;
	mat.amb_color = vec_create(1.0, 1.0, 1.0);
	mat.amb_int = 0.0;
	return (mat);
}

t_vec	spl_compute_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	//Define the initials materials colors
	t_vec	m_color = vec_create(0.0, 0.0, 0.0);
	t_vec	r_color = vec_create(0.0, 0.0, 0.0);
	t_vec	d_color = vec_create(0.0, 0.0, 0.0);
	t_vec	s_color = vec_create(0.0, 0.0, 0.0);
	(void)r_color;

	//Apply any normal maps
	if (poi.obj->mat.has_nmap)
	{
		poi.normal = nmap_compute_perturb(poi.obj->mat.nmap, poi.normal, poi.u, poi.v);
	}

	//Compute the diffuse component
	if (!poi.obj->mat.has_texture)
		d_color = diff_color(scene, poi, poi.obj->mat.color);
	else
	{
		d_color = diff_color(scene, poi,
							 poi.obj->mat.texture.colorfct(
												  poi.obj->mat.texture,
												  poi.u, poi.v));
	}

	//Compute the reflection color
	if (poi.obj->mat.reflec > 0.0)
	{
		r_color = ref_color(scene, in_ray, poi);
	}

	//Combine reflection and diffuse component
	m_color = vec_add(vec_mult(r_color, poi.obj->mat.reflec), vec_mult(d_color, 1.0 - poi.obj->mat.reflec));


	//Compute the specular component
	if (poi.obj->mat.shiny > 1.0)
	{
		s_color = spec_color(scene, in_ray, poi);
	}

	//Add the spec to the final color
	m_color = vec_add(m_color, s_color);

	return (m_color);
}

/*t_vec	spl_compute_color(t_obj *obj_lst, t_light *light_lst, t_poi poi,
						   t_ray cam_ray, t_material mat)
{
	//Define the initials materials colors
	t_vec	mat_color = vec_create(0.0, 0.0, 0.0);
	t_vec	ref_color = vec_create(0.0, 0.0, 0.0);
	t_vec	dif_color = vec_create(0.0, 0.0, 0.0);
	t_vec	spec_color = vec_create(0.0, 0.0, 0.0);
	(void)ref_color;

	//Apply any normal maps
	if (poi.obj->mat.has_nmap)
	{
		poi.normal = nmap_compute_perturb(poi.obj->mat.nmap, poi.normal, poi.u, poi.v);
	}

	//Compute the diffuse component
	if (!poi.obj->mat.has_texture)
	{
		dif_color = diff_color(obj_lst, light_lst, poi,
										  poi.obj->mat.color);
	}
	else
	{
		dif_color = diff_color(obj_lst, light_lst, poi,
										  poi.obj->mat.texture.colorfct(
												  poi.obj->mat.texture,
												  poi.u, poi.v));
	}

	//Compute the reflection color
	if (mat.reflec > 0.0)
	{
		ref_color = ref_color(obj_lst, light_lst, poi, cam_ray, poi.obj->mat);
	}

	//Combine reflection and diffuse component
	mat_color = vec_add(vec_mult(ref_color, mat.reflec), vec_mult(dif_color, 1.0 - mat.reflec));


	//Compute the specular component
	if (mat.shiny > 0.0)
	{
		spec_color = spec_color(obj_lst, light_lst, poi, cam_ray, poi.obj->mat);
	}

	//Add the spec to the final color
	mat_color = vec_add(mat_color, spec_color);

	return (mat_color);
}*/
