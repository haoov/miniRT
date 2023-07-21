/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:17:58 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:18:35 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "object.h"
#include "miniRT.h"
#include "mlx_app.h"
#include "normal_map.h"

t_normal_map	normal_map_create(void)
{
	t_normal_map	map;

	ft_memset(&map, 0, sizeof (t_normal_map));
	return (map);
}

void	assign_nmap(t_material *mat, t_normal_map map)
{
	mat->nmap = map;
	mat->has_nmap = true;
}

t_vec	nmap_apply(t_normal_map map, t_vec normal, double u, double v)
{
	t_vec	new_loc;
	int		x;
	int		y;
	int		pixel_index;
	t_vec	rgb;

	new_loc = apply_transform(map.tfm, vec_create(u, v, 0.0));
	x = (int)(round(((new_loc.x + 1.0) / 2.0) * (double) map.img.size_x));
	y = map.img.size_y - ((int)(round(((new_loc.y + 1.0) / 2.0)
					* (double) map.img.size_y)));
	x = ((x % map.img.size_x) + map.img.size_x) % map.img.size_x;
	y = ((y % map.img.size_y) + map.img.size_y) % map.img.size_y;
	pixel_index = y * map.img.bpl + x * (map.img.bpp / 8);
	rgb = nmap_extract_rgb(map.img, pixel_index);
	return (perturb_normal(normal, rgb));
}

t_vec	perturb_normal(t_vec normal, t_vec perturbation)
{
	t_vec	up_vec;
	t_vec	pv;
	t_vec	pu;
	t_vec	output;

	up_vec = vec_create(0.0, 0.0, -1.0);
	if (normal.z > 0.99 || normal.z < -0.99)
		up_vec = vec_create(1.0, 0.0, 0.0);
	pv = vec_cross(up_vec, normal);
	vec_normalize(&pv);
	pu = vec_cross(normal, pv);
	vec_normalize(&pu);
	output = vec_add(normal, vec_mult(pu, perturbation.x));
	output = vec_add(output, vec_mult(pv, perturbation.y));
	output = vec_add(output, vec_mult(normal, perturbation.z));
	vec_normalize(&output);
	return (output);
}
