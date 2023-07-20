/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:00:50 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 11:00:51 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "scene.h"

double	compute_spec_intensity(t_light light, t_ray in_ray, t_poi poi)
{
	t_vec	d;
	t_vec	r;
	double	dot;
	double	intensity;

	intensity = 0.0;
	d = generate_light_ray(poi, light).ab;
	r = vec_sub(d, vec_mult(poi.normal, 2 * vec_dot(d, poi.normal)));
	vec_normalize(&r);
	dot = vec_dot(r, vec_normalized(in_ray.ab));
	if (dot > 0.0)
		intensity = poi.obj->mat.reflec * pow(dot, poi.obj->mat.shiny);
	return (intensity);
}

t_vec	spec_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	s_color;
	double	intensity;

	s_color = vec_create(0.0, 0.0, 0.0);
	while (scene.light_lst != NULL)
	{
		intensity = 0.0;
		if (illum(scene, &poi, *scene.light_lst))
		{
			intensity = compute_spec_intensity(*scene.light_lst, in_ray, poi);
		}
		s_color = vec_add(s_color, vec_mult(scene.light_lst->color, intensity));
		scene.light_lst = scene.light_lst->next;
	}
	return (s_color);
}

/*t_vec	spec_color(t_scene scene, t_ray in_ray, t_poi poi)
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
}*/

/*t_vec	spec_color(t_obj *obj_lst, t_light *light_lst,
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
