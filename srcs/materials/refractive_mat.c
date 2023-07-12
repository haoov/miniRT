# include "material.h"
# include "object.h"

static t_vec	compute_trans_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
									t_poi poi, t_ray in_ray, t_material mat);

t_material	refractive_mat_const(t_vec color, double ref, double shiny,
								   double trans)
{
	t_material	mat;

	mat.color = color;
	mat.reflec = ref;
	mat.shiny = shiny;
	mat.translucency = trans;
	mat.ior = 1.0;
	mat.max_ref_ray = 3;
	mat.ref_ray_count = 0;
	mat.has_texture = false;
	mat.colorfct = ref_compute_color;
	mat.ambiant_color = vec_create(1.0, 1.0, 1.0);
	mat.ambiant_intensity = 0.0;
	return (mat);
}

t_vec	ref_compute_color(t_obj_lst *obj_lst, t_light_lst *light_lst, t_poi poi,
						   t_ray cam_ray, t_material mat)
{
	//Define the initials materials colors
	t_vec	mat_color = vec_create(0.0, 0.0, 0.0);
	t_vec	ref_color = vec_create(0.0, 0.0, 0.0);
	t_vec	dif_color = vec_create(0.0, 0.0, 0.0);
	t_vec	spec_color = vec_create(0.0, 0.0, 0.0);
	t_vec	trn_color = vec_create(0.0, 0.0, 0.0);

	//Compute the diffuse component
	if (!poi.obj->material.has_texture)
		dif_color = compute_diffuse_color(obj_lst, light_lst, poi, mat.color);
	else
		dif_color = compute_diffuse_color(obj_lst, light_lst, poi,
										  mat.texture.colorfct(mat.texture,
												  poi.u, poi.v));

	//Compute the reflection color
	if (mat.reflec > 0.0)
		ref_color = compute_ref_color(obj_lst, light_lst, poi, cam_ray,
									  poi.obj->material);

	//Combine reflection and diffuse component
	mat_color = vec_add(vec_mult(ref_color, mat.reflec),
						vec_mult(dif_color, 1.0 - mat.reflec));

	//Compute the refractive component
	if (mat.translucency > 0.0)
		trn_color = compute_trans_color(obj_lst, light_lst, poi, cam_ray, mat);

	//Combine with the current color
	mat_color = vec_add(vec_mult(trn_color, mat.translucency),
						vec_mult(mat_color, 1.0 - mat.translucency));

	//And compute the specular component
	if (mat.shiny > 0.0)
		spec_color = compute_spec_color(obj_lst, light_lst, poi, cam_ray, mat);

	//Add the specular component
	mat_color = vec_add(mat_color, spec_color);

	return (mat_color);
}

static t_vec	compute_trans_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
								   t_poi poi, t_ray in_ray, t_material mat)
{
	t_vec	trn_color;

	//Compute the refractive vector
	t_vec	p;
	t_vec	tempnormal;
	double	r;
	double	c;
	t_vec	ref_vec;

	p = in_ray.ab;
	vec_normalize(&p);
	tempnormal = poi.normal;
	r = 1.0 / mat.ior;
	c = -vec_dot(tempnormal, p);
/*	if (c < 0.0)
	{
		tempnormal = vec_mult(tempnormal, -1.0);
		c = -vec_dot(tempnormal, p);
	}*/
	ref_vec = vec_add(vec_mult(p, r),
					  vec_mult(tempnormal, r * c - sqrt(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)))));

	//Construct the refracted ray
	t_ray	ref_ray;

	ref_ray = ray_create(vec_add(poi.point, vec_mult(ref_vec, 0.01)),
						 vec_add(poi.point, ref_vec));

	//Test for secondery intersection with this object
	t_poi	closest_poi;
	t_poi	new_poi;
	bool	test = false;
	bool	int_found = false;
	t_ray	final_ray;

	//Test for intersection with possible objects inside the current one
	int_found = cast_ray(ref_ray, &closest_poi, obj_lst, poi.obj);

	if (!int_found)
		test = poi.obj->intfct(ref_ray, &new_poi, poi.obj);
	if (!int_found && test)
	{
		//printf("secondary interserct\n");
		//Compute the refracted vector
		t_vec	p2;
		t_vec	tempnormal2;
		double	r2;
		double	c2;
		t_vec	ref_vec2;

		p2 = ref_ray.ab;
		vec_normalize(&p2);
		tempnormal2 = new_poi.normal;
		r2 = mat.ior;
		c2 = -vec_dot(tempnormal2, p2);
		if (c2 < 0.0)
		{
			tempnormal2 = vec_mult(tempnormal2, -1.0);
			c2 = -vec_dot(tempnormal2, p2);
		}
		ref_vec2 = vec_add(vec_mult(p2, r2),
						  vec_mult(tempnormal2, r2 * c2 - sqrt(1.0 - pow(r2, 2.0) * (1.0 - pow(c2, 2.0)))));

		//Construct the refracted ray
		t_ray	ref_ray2;

		ref_ray2 = ray_create(vec_add(new_poi.point, vec_mult(ref_vec2, 0.01)),
							  vec_add(new_poi.point, ref_vec2));

		//Cast the ray into the scene
		int_found = cast_ray(ref_ray2, &closest_poi, obj_lst, poi.obj);
		final_ray = ref_ray2;
	}
	else if (!test)
	{
		//No secondary intersection
		int_found = cast_ray(ref_ray, &closest_poi, obj_lst, poi.obj);
		final_ray = ref_ray;
	}

	//Compute the color for closest object
	t_vec	mat_color = vec_create(0.0, 0.0, 0.0);
	if (int_found)
	{
		if (closest_poi.obj->has_material)
			mat_color = closest_poi.obj->material.colorfct(obj_lst, light_lst,
														   closest_poi, final_ray,
														   closest_poi.obj->material);
		else
			mat_color = compute_diffuse_color(obj_lst, light_lst, closest_poi,
											  closest_poi.obj->color);
	}
	else
	{
		//Leave mat_color as it is
	}
	trn_color = mat_color;
	return (trn_color);
}
