/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:19:57 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 09:34:12 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "scene.h"
#include <math.h>

double	dist(t_vec v1, t_vec v2)
{
	double	dist;

	dist = vec_norm(vec_sub(v2, v1));
	return (dist);
}

t_ray	generate_light_ray(t_poi poi, t_light light)
{
	t_ray	light_ray;
	t_vec	light_vec;

	light_vec = vec_normalized(vec_sub(light.pos, poi.point));
	light_ray = ray_create(poi.point, vec_add(poi.point, light_vec));
	return (light_ray);
}

bool	obstruction(t_scene scene, t_poi *poi, t_light light)
{
	t_ray	light_ray;
	t_poi	obsp;
	bool	obs;

	light_ray = generate_light_ray(*poi, light);
	obs = false;
	while (scene.obj_lst != NULL)
	{
		if (scene.obj_lst != poi->obj)
		{
			obs = scene.obj_lst->intfct(light_ray, &obsp, scene.obj_lst);
			if (obs && (poi->obj->mat.trans > 0.0
					|| dist(poi->point, obsp.point)
					> dist(obsp.point, light.pos)))
				obs = false;
		}
		if (obs)
			break ;
		scene.obj_lst = scene.obj_lst->next;
	}
	return (obs);
}

bool	illum(t_scene scene, t_poi *poi, t_light light)
{
	double	angle;
	t_vec	light_dir;

	if (obstruction(scene, poi, light))
		return (false);
	else
	{
		light_dir = vec_normalized(vec_sub(light.pos, poi->point));
		angle = acos(vec_dot(poi->normal, light_dir));
		if (angle > M_PI_2)
			return (false);
		else
		{
			poi->color = light.color;
			poi->intensity = light.intensity * (1.0 - (angle / M_PI_2));
			return (true);
		}
	}
}

/*bool	illum(t_scene scene, t_poi *poi, t_light light)
{
	t_vec	lightdir; //Vector from the point to the light
	double	angle; //angle between the normal and the light ray

	lightdir = vec_sub(light.pos, poi->point);
	vec_normalize(&lightdir);

	//Compute a starting point
	t_vec	start_point;
	start_point = poi->point;

	//Construct a ray from the point of intersection to the light
	t_ray	light_ray;
	light_ray = ray_create(start_point, vec_add(start_point, lightdir));

	//check for intersection with all of the object exept the current one
	t_poi	poi_obs;
	bool	valid_int = false;

	while (scene.obj_lst != NULL)
	{
		if (scene.obj_lst != poi->obj)
		{
			valid_int = scene.obj_lst->intfct(light_ray, &poi_obs, scene.obj_lst);
			if (valid_int && poi_obs.obj->mat.trans)
				valid_int = false;
			if (valid_int)
			{
				double	light_dist = vec_norm(vec_sub(light.pos, poi_obs.point));
				double	dist = vec_norm(vec_sub(poi_obs.point, start_point));
				if (dist > light_dist)
					valid_int = false;
			}
		}


		if (valid_int)
		{
			break;
		}
		scene.obj_lst = scene.obj_lst->next;
	}

	//Only continue if the light ray didnt intersect with anything
	if (!valid_int)
	{
		//Compute the angle between the normal amd the lightray
		angle = acos(vec_dot(poi->normal, lightdir));

		//If the normal is pointing away from the light then no illumination
		if (angle > M_PI_2)
		{
			//No illum
			poi->color = light.color;
			poi->intensity = 0.0;
			return (false);
		}
		else
		{
			//Illum
			poi->color = light.color;
			poi->intensity = light.intensity * (1.0 - (angle / M_PI_2));
			return (true);
		}
	}
	else
	{
		//Shadow
		poi->color = light.color;
		poi->intensity = 0.0;
		return (false);
	}
}*/
