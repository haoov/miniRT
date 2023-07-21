/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:42:39 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 10:42:40 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtfm.h"

t_gtfm	gtfm_set(t_vec trans, t_vec rot, t_vec scale)
{
	t_gtfm	gtfm;

	rot = vec_mult(rot, M_PI / 180);
	gtfm.tfm_mtx = mtx4_mult(trans_mtx(trans), rotx_mtx(rot));
	gtfm.tfm_mtx = mtx4_mult(gtfm.tfm_mtx, roty_mtx(rot));
	gtfm.tfm_mtx = mtx4_mult(gtfm.tfm_mtx, rotz_mtx(rot));
	gtfm.tfm_mtx = mtx4_mult(gtfm.tfm_mtx, scale_mtx(scale));
	gtfm.revtfm_mtx = gtfm.tfm_mtx;
	mtx4_invert(&gtfm.revtfm_mtx);
	return (gtfm);
}

t_vec	gtfm_vec_apply(t_gtfm gtfm, t_vec vec, int tfm)
{
	t_vec4	vec4;
	t_vec4	tmp_res;
	t_vec	res;

	vec4 = vec4_create(vec.x, vec.y, vec.z, 1.0);
	if (tfm == FWD)
	{
		tmp_res = mtx4_vec_mult(vec4, gtfm.tfm_mtx);
	}
	else
	{
		tmp_res = mtx4_vec_mult(vec4, gtfm.revtfm_mtx);
	}
	res = vec_create(tmp_res.x, tmp_res.y, tmp_res.z);
	return (res);
}

t_ray	gtfm_ray_apply(t_gtfm gtfm, t_ray ray, int tfm)
{
	t_ray	tfm_ray;

	tfm_ray.pa = gtfm_vec_apply(gtfm, ray.pa, tfm);
	tfm_ray.pb = gtfm_vec_apply(gtfm, ray.pb, tfm);
	tfm_ray.ab = vec_sub(tfm_ray.pb, tfm_ray.pa);
	return (tfm_ray);
}
