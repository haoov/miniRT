/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_mat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:19:59 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 11:22:40 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "scene.h"

#include "stdio.h"

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

t_vec	compute_ref_diff(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec		r_color;
	t_vec		d_color;
	t_texture	txtr;
	t_vec		res_color;

	r_color = vec_create(0.0, 0.0, 0.0);
	if (poi.obj->mat.has_texture)
	{
		txtr = poi.obj->mat.texture;
		d_color = diff_color(scene, poi, txtr.colorfct(txtr, poi.u, poi.v));
	}
	else
	{
		d_color = diff_color(scene, poi, poi.obj->mat.color);
	}
	if (poi.obj->mat.reflec > 0.0)
	{
		r_color = ref_color(scene, in_ray, poi);
	}
	res_color = vec_add(vec_mult(r_color, poi.obj->mat.reflec),
			vec_mult(d_color, 1.0 - poi.obj->mat.reflec));
	return (res_color);
}

t_vec	spl_compute_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	m_color;
	t_vec	s_color;

	s_color = vec_create(0.0, 0.0, 0.0);
	if (poi.obj->mat.has_nmap)
		poi.normal = nmap_apply(poi.obj->mat.nmap, poi.normal, poi.u, poi.v);
	m_color = compute_ref_diff(scene, in_ray, poi);
	if (poi.obj->mat.shiny > 1.0)
	{
		s_color = spec_color(scene, in_ray, poi);
	}
	m_color = vec_add(m_color, s_color);
	return (m_color);
}
