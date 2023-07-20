/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:59:50 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 11:00:11 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "scene.h"

t_vec	diff_color(t_scene scene, t_poi poi, t_vec b_color)
{
	t_vec	d_color;
	t_vec	rgb;
	bool	valid_illum;

	valid_illum = false;
	d_color = vec_create(0.0, 0.0, 0.0);
	rgb = vec_mult(scene.amb_color, scene.amb_int);
	while (scene.light_lst != NULL)
	{
		valid_illum = illum(scene, &poi, *scene.light_lst);
		if (valid_illum)
		{
			rgb = vec_add(rgb, vec_mult(poi.color, poi.intensity));
		}
		scene.light_lst = scene.light_lst->next;
	}
	d_color.x = rgb.x * b_color.x;
	d_color.y = rgb.y * b_color.y;
	d_color.z = rgb.z * b_color.z;
	return (d_color);
}

/*t_vec	diff_color(t_obj *obj_lst, t_light *light_lst,
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
		valid_illum = illum(&poi.point, &poi.normal, &color, &intensity,
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
