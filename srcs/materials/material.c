#include "material.h"
#include "scene.h"

#include "stdio.h"

void	assign_material(t_obj *obj, t_material material)
{
	obj->mat = material;
	obj->has_mat = true;
}

t_vec	compute_diffuse_color(t_scene scene, t_poi poi, t_vec b_color)
{
	t_vec	diff_color;
	t_vec	color;
	t_vec	rgb;
	double	intensity;
	bool	valid_illum = false;
	bool	illum_found = false;

	//Compute the color due to diffuse illum
	diff_color = vec_create(0.0, 0.0, 0.0);
	rgb = vec_create(0.0, 0.0, 0.0);
	while (scene.light_lst != NULL)
	{
		valid_illum = point_illum(&poi.point, &poi.normal, &color, &intensity,
								  scene.light_lst, scene.obj_lst, poi.obj);
		if (valid_illum)
		{
			illum_found = true;
			rgb = vec_add(rgb, vec_mult(color, intensity));
		}
		scene.light_lst = scene.light_lst->next;
	}
	if (illum_found)
	{
		diff_color.x = rgb.x * b_color.x;
		diff_color.y = rgb.y * b_color.y;
		diff_color.z = rgb.z * b_color.z;
	}
	else
	{
		//The ambiant conditions
		diff_color.x = scene.amb_color.x * scene.amb_int * b_color.x;
		diff_color.y = scene.amb_color.y * scene.amb_int * b_color.y;
		diff_color.z = scene.amb_color.z * scene.amb_int * b_color.z;
	}
	return (diff_color);
}

/*t_vec	compute_diffuse_color(t_obj *obj_lst, t_light *light_lst,
							   t_poi poi, t_vec base_color)
{
	t_vec	diff_color;
	t_vec	color;
	t_vec	rgb;
	double	intensity;
	bool	valid_illum = false;
	bool	illum_found = false;

	//Compute the color due to diffuse illum
	diff_color = vec_create(0.0, 0.0, 0.0);
	rgb = vec_create(0.0, 0.0, 0.0);
	while (light_lst != NULL)
	{
		valid_illum = point_illum(&poi.point, &poi.normal, &color, &intensity,
								  light_lst, obj_lst, poi.obj);
		if (valid_illum)
		{
			illum_found = true;
			rgb = vec_add(rgb, vec_mult(color, intensity));
		}
		light_lst = light_lst->next;
	}
	if (illum_found)
	{
		diff_color.x = rgb.x * base_color.x;
		diff_color.y = rgb.y * base_color.y;
		diff_color.z = rgb.z * base_color.z;
	}
	else
	{
		//The ambiant conditions
		diff_color.x = poi.obj->mat.amb_color.x * poi.obj->mat.amb_int * base_color.x;
		diff_color.y = poi.obj->mat.amb_color.y * poi.obj->mat.amb_int * base_color.y;
		diff_color.z = poi.obj->mat.amb_color.z * poi.obj->mat.amb_int * base_color.z;
	}
	return (diff_color);
}*/

t_vec	compute_ref_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	ref_color = vec_create(0.0, 0.0, 0.0);

	//Compute the reflection vector
	t_vec	d = in_ray.ab;
	t_vec	ref_vector = vec_sub(d, vec_mult(poi.normal, 2 * vec_dot(d, poi.normal)));

	//Construct the reflection ray
	t_ray	ref_ray = ray_create(poi.point, vec_add(poi.point, ref_vector));

	//Cast this ray into the scene and find the closest object it intersect with
	t_poi	closest_poi;
	bool	int_found = cast_ray(ref_ray, &closest_poi, scene.obj_lst, poi.obj);

	//Compute illum for closest object
	t_vec	mat_color = vec_create(0.0, 0.0, 0.0);
	if (int_found && poi.obj->mat.ref_ray_count < poi.obj->mat.max_ref_ray)
	{
		//Increment the ref count
		poi.obj->mat.ref_ray_count++;

		//Check if mat
		if (closest_poi.obj->has_mat)
		{
			//Use the mat to compute the color
			mat_color = poi.obj->mat.colorfct(scene, ref_ray, closest_poi);
		}
		else
		{
			mat_color = compute_diffuse_color(scene, closest_poi,
											  closest_poi.obj->color);
		}
	}
	ref_color = mat_color;
	return (ref_color);
}

/*t_vec	compute_ref_color(t_obj *obj_lst, t_light *light_lst,
						   t_poi poi, t_ray incident_ray, t_material mat)
{
	t_vec	ref_color = vec_create(0.0, 0.0, 0.0);

	//Compute the reflection vector
	t_vec	d = incident_ray.ab;
	t_vec	ref_vector = vec_sub(d, vec_mult(poi.normal, 2 * vec_dot(d, poi.normal)));

	//Construct the reflection ray
	t_ray	ref_ray = ray_create(poi.point, vec_add(poi.point, ref_vector));

	//Cast this ray into the scene and find the closest object it intersect with
	t_poi	closest_poi;
	bool	int_found = cast_ray(ref_ray, &closest_poi, obj_lst, poi.obj);

	//Compute illum for closest object
	t_vec	mat_color = vec_create(0.0, 0.0, 0.0);
	if (int_found && mat.ref_ray_count < mat.max_ref_ray)
	{
		//Increment the ref count
		mat.ref_ray_count++;

		//Check if mat
		if (closest_poi.obj->has_mat)
		{
			//Use the mat to compute the color
			mat_color = poi.obj->mat.colorfct(obj_lst, light_lst, closest_poi, ref_ray,
											  closest_poi.obj->mat);
		}
		else
		{
			mat_color = compute_diffuse_color(obj_lst, light_lst, closest_poi,
											  closest_poi.obj->color);
		}
	}
	ref_color = mat_color;
	return (ref_color);
}*/

t_vec	compute_spec_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	spc_color = vec_create(0.0, 0.0, 0.0);
	t_vec	rgb = vec_create(0.0, 0.0, 0.0);
	while (scene.light_lst != NULL)
	{
		//Check for intersect with all objects in the scene
		double	intensity = 0.0;

		//Construct a vector pointing from the poi to the light
		t_vec	light_dir;
		light_dir = vec_sub(scene.light_lst->pos, poi.point);
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

		while (scene.obj_lst != NULL)
		{
			valid_int = scene.obj_lst->intfct(light_ray, &ob_poi, scene.obj_lst);
			if (valid_int)
			{
				break;
			}
			scene.obj_lst = scene.obj_lst->next;
		}
		if (!valid_int)
		{
			//Compute the reflection vector
			t_vec	d = light_ray.ab;
			t_vec	r = vec_sub(d, vec_mult(poi.normal, 2 * vec_dot(d, poi.normal)));
			vec_normalize(&r);

			//Compute the dot product
			t_vec	v = in_ray.ab;
			vec_normalize(&v);
			double	dot = vec_dot(r, v);

			//Only proceed if the dot product is positive
			if (dot > 0.0)
			{
				intensity = poi.obj->mat.reflec * pow(dot, poi.obj->mat.shiny);
			}
		}
		rgb = vec_add(rgb, vec_mult(scene.light_lst->color, intensity));
		scene.light_lst = scene.light_lst->next;
	}
	spc_color = rgb;
	return (spc_color);
}

/*t_vec	compute_spec_color(t_obj *obj_lst, t_light *light_lst,
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
		light_dir = vec_sub(light_lst->pos, poi.point);
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
		rgb = vec_add(rgb, vec_mult(light_lst->color, intensity));
		light_lst = light_lst->next;
	}
	spc_color = rgb;
	return (spc_color);
}*/

bool	cast_ray(t_ray cast_ray, t_poi *closest_poi, t_obj *obj_lst, t_obj *obj_cur)
{
	t_poi	poi;
	bool	intersection;
	bool	int_found;
	double	dist;
	double	min_dist;

	min_dist = 1e6;
	int_found = false;
	intersection = false;
	while (obj_lst != NULL)
	{
		//Test intersection
		if (obj_lst != obj_cur)
		{
			intersection = obj_lst->intfct(cast_ray, &poi, obj_lst);
		}

		if (intersection)
		{
			int_found = true;
			//Compute the distance between the camera and the poi
			dist = vec_norm(vec_sub(poi.point, cast_ray.pa));

			//If this object is closer to the cam than the others
			if (dist < min_dist)
			{
				min_dist = dist;
				*closest_poi = poi;
			}
		}
		obj_lst = obj_lst->next;
	}
	return (int_found);
}
