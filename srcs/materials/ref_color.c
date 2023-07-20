/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:00:34 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 11:00:35 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "scene.h"

t_ray	generate_reflection_ray(t_ray in_ray, t_poi poi)
{
	t_vec	d;
	t_vec	r_dir;
	t_ray	r_ray;

	d = in_ray.ab;
	r_dir = vec_sub(d, vec_mult(poi.normal, 2 * vec_dot(d, poi.normal)));
	r_ray = ray_create(poi.point, vec_add(poi.point, r_dir));
	return (r_ray);
}

t_vec	ref_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	r_color;
	t_ray	r_ray;
	t_poi	test;
	bool	intersection;

	r_color = vec_create(0.0, 0.0, 0.0);
	r_ray = generate_reflection_ray(in_ray, poi);
	intersection = cast_ray(r_ray, &test, scene.obj_lst, poi.obj);
	if (intersection && poi.obj->mat.ref_ray_count < poi.obj->mat.max_ref_ray)
	{
		poi.obj->mat.ref_ray_count++;
		if (test.obj->has_mat)
			r_color = poi.obj->mat.colorfct(scene, r_ray, test);
		else
			r_color = diff_color(scene, test, test.obj->color);
	}
	return (r_color);
}

/*t_vec	ref_color(t_scene scene, t_ray in_ray, t_poi poi)
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
			mat_color = diff_color(scene, closest_poi,
								   closest_poi.obj->color);
		}
	}
	ref_color = mat_color;
	return (ref_color);
}*/

/*t_vec	ref_color(t_obj *obj_lst, t_light *light_lst,
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
			mat_color = diff_color(obj_lst, light_lst, closest_poi,
											  closest_poi.obj->color);
		}
	}
	ref_color = mat_color;
	return (ref_color);
}*/
