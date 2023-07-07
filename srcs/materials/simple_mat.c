#include "material.h"

static t_vec	compute_spec_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
							t_poi poi, t_ray cam_ray, t_material mat);

t_material	simple_mat_const(t_vec color, double ref, double shiny)
{
	t_material	mat;

	mat.color = color;
	mat.reflec = ref;
	mat.shiny = shiny;
	mat.max_ref_ray = 3;
	mat.ref_ray_count = 0;
	mat.has_texture = false;
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
	{
		dif_color = compute_diffuse_color(obj_lst, light_lst, poi,
										  poi.obj->material.color);
	}
	else
	{
		dif_color = compute_diffuse_color(obj_lst, light_lst, poi,
										  poi.obj->material.texture.colorfct(
												  poi.obj->material.texture,
												  poi.u, poi.v));
	}

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

static t_vec	compute_spec_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
							t_poi poi, t_ray cam_ray, t_material mat)
{
	t_vec	spc_color = vec_create(0.0, 0.0, 0.0);
	t_vec	rgb = vec_create(0.0, 0.0, 0.0);
	while (light_lst != NULL)
	{
		//Check for intersect with all objects in the scene
		double	intensity = 0.0;

		//Construct a vector pointing from the poi to the light
		t_vec	light_dir;
		light_dir = vec_sub(light_lst->light.pos, poi.point);
		vec_normalize(&light_dir);

		//Compute a start point
		t_vec	start_point;
		start_point = vec_add(poi.point, vec_mult(light_dir, 0.001));

		//Construct a ray from the poi to the light
		t_ray	light_ray;
		light_ray = ray_create(start_point, vec_add(start_point, light_dir));

		//Loop trough all objects to see if any obstruct
		t_poi	ob_poi;
		bool	valid_int = false;

		while (obj_lst != NULL)
		{
			valid_int = obj_lst->intfct(light_ray, &ob_poi, obj_lst);
			if (valid_int)
			{
				break;
			}
			obj_lst = obj_lst->next;
		}
		if (!valid_int)
		{
			//Compute the reflection vector
			t_vec	d = light_ray.ab;
			t_vec	r = vec_sub(d, vec_mult(poi.normal, 2 * vec_dot(d, poi.normal)));
			vec_normalize(&r);

			//Compute the dot product
			t_vec	v = cam_ray.ab;
			vec_normalize(&v);
			double	dot = vec_dot(r, v);

			//Only proceed if the dot product is positive
			if (dot > 0.0)
			{
				intensity = mat.reflec * pow(dot, mat.shiny);
			}
		}
		rgb = vec_add(rgb, vec_mult(light_lst->light.color, intensity));
		light_lst = light_lst->next;
	}
	spc_color = rgb;
	return (spc_color);
}
