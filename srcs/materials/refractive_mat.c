/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractive_mat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:54:29 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 11:55:31 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "object.h"
#include "scene.h"

static t_vec	compute_trans_color(t_scene scene, t_ray in_ray, t_poi poi);

t_material	refractive_mat_const(t_vec color, double ref, double shiny,
									double trans)
{
	t_material	mat;

	ft_memset(&mat, 0, sizeof (t_material));
	mat.color = color;
	mat.reflec = ref;
	mat.shiny = shiny;
	mat.trans = trans;
	mat.ior = 1.0;
	mat.max_ref_ray = 3;
	mat.ref_ray_count = 0;
	mat.has_texture = false;
	mat.colorfct = ref_compute_color;
	mat.amb_color = vec_create(1.0, 1.0, 1.0);
	mat.amb_int = 0.0;
	return (mat);
}

t_vec	ref_compute_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	m_color;
	t_vec	s_color;
	t_vec	t_color;

	s_color = vec_create(0.0, 0.0, 0.0);
	t_color = vec_create(0.0, 0.0, 0.0);
	if (poi.obj->mat.has_nmap)
		poi.normal = nmap_apply(poi.obj->mat.nmap, poi.normal, poi.u, poi.v);
	m_color = compute_ref_diff(scene, in_ray, poi);
	if (poi.obj->mat.trans > 0.0)
		t_color = compute_trans_color(scene, in_ray, poi);
	m_color = vec_add(vec_mult(t_color, poi.obj->mat.trans),
			vec_mult(m_color, 1.0 - poi.obj->mat.trans));
	if (poi.obj->mat.shiny > 1.0)
		s_color = spec_color(scene, in_ray, poi);
	m_color = vec_add(m_color, s_color);
	return (m_color);
}

t_vec	compute_refractive_vec(t_ray in_ray, t_poi poi)
{
	t_vec	p;
	t_vec	tempnormal;
	double	r;
	double	c;
	t_vec	ref_vec;

	p = in_ray.ab;
	vec_normalize(&p);
	tempnormal = poi.normal;
	r = 1.0 / poi.obj->mat.ior;
	c = -vec_dot(tempnormal, p);
	if (c < 0.0)
	{
		tempnormal = vec_mult(tempnormal, -1.0);
		c = -vec_dot(tempnormal, p);
	}
	ref_vec = vec_add(vec_mult(p, r),
			vec_mult(tempnormal,
				r * c - sqrt(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)))));
	return (ref_vec);
}

t_ray	generate_refractive_ray(t_ray in_ray, t_poi poi)
{
	t_vec	ref_vec;
	t_ray	ref_ray;

	ref_vec = compute_refractive_vec(in_ray, poi);
	ref_ray = ray_create(vec_add(poi.point, vec_mult(ref_vec, 0.01)),
			vec_add(poi.point, ref_vec));
	return (ref_ray);
}

t_vec	compute_trans_color(t_scene scene, t_ray in_ray, t_poi poi)
{
	t_vec	t_color;
	t_ray	r_ray;
	t_poi	new_poi;
	bool	intersection;
	bool	inside_int;

	t_color = vec_create(0.0, 0.0, 0.0);
	intersection = false;
	r_ray = generate_refractive_ray(in_ray, poi);
	inside_int = cast_ray(in_ray, &new_poi, scene.obj_lst, poi.obj);
	if (!inside_int)
		intersection = poi.obj->intfct(r_ray, &new_poi, poi.obj);
	if (intersection)
		r_ray = generate_refractive_ray(r_ray, new_poi);
	intersection = cast_ray(r_ray, &new_poi, scene.obj_lst, poi.obj);
	if (intersection)
	{
		if (new_poi.obj->has_mat)
			t_color = new_poi.obj->mat.colorfct(scene, r_ray, new_poi);
		else
			t_color = diff_color(scene, new_poi, new_poi.obj->color);
	}
	return (t_color);
}
