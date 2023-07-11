#include "gtfm.h"

#include <stdio.h>

t_mtx3	compute_lin_tfm(t_mtx4 tfm_mtx);

void	init_gtfm(t_gtfm *gtfm)
{
	mtx4_identity(&gtfm->tfm_mtx);
	mtx4_identity(&gtfm->revtfm_mtx);
	mtx3_identity(&gtfm->lin_tfm_mtx);
}

t_gtfm	gtfm_set(t_vec trans, t_vec rot, t_vec scale)
{
	t_gtfm	gtfm;

	//Define a matric for each component
	t_mtx4	trans_mtx;
	t_mtx4	rotx_mtx;
	t_mtx4	roty_mtx;
	t_mtx4 	rotz_mtx;
	t_mtx4	scale_mtx;

	//Set the matrix to mtx4_identity
	mtx4_identity(&trans_mtx);
	mtx4_identity(&rotx_mtx);
	mtx4_identity(&roty_mtx);
	mtx4_identity(&rotz_mtx);
	mtx4_identity(&scale_mtx);

	//Set values
	//Translation
	trans_mtx.val[0][3] = trans.x;
	trans_mtx.val[1][3] = trans.y;
	trans_mtx.val[2][3] = trans.z;

	//rotation
	rotx_mtx.val[1][1] = cos(rot.x);
	rotx_mtx.val[1][2] = -sin(rot.x);
	rotx_mtx.val[2][1] = sin(rot.x);
	rotx_mtx.val[2][2] = cos(rot.x);

	roty_mtx.val[0][0] = cos(rot.y);
	roty_mtx.val[0][2] = sin(rot.y);
	roty_mtx.val[2][0] = -sin(rot.y);
	roty_mtx.val[2][2] = cos(rot.y);

	rotz_mtx.val[0][0] = cos(rot.z);
	rotz_mtx.val[0][1] = -sin(rot.z);
	rotz_mtx.val[1][0] = sin(rot.z);
	rotz_mtx.val[1][1] = cos(rot.z);

	//Scaling
	scale_mtx.val[0][0] = scale.x;
	scale_mtx.val[1][1] = scale.y;
	scale_mtx.val[2][2] = scale.z;

	//Combine to the final foward matrix
	gtfm.tfm_mtx = mtx4_mult(trans_mtx, rotx_mtx);
	gtfm.tfm_mtx = mtx4_mult(gtfm.tfm_mtx, roty_mtx);
	gtfm.tfm_mtx = mtx4_mult(gtfm.tfm_mtx, rotz_mtx);
	gtfm.tfm_mtx = mtx4_mult(gtfm.tfm_mtx, scale_mtx);

	//Compute the revtfm
	gtfm.revtfm_mtx = gtfm.tfm_mtx;
	mtx4_invert(&gtfm.revtfm_mtx);
	gtfm.lin_tfm_mtx = compute_lin_tfm(gtfm.tfm_mtx);
	return (gtfm);
}

t_mtx3	compute_lin_tfm(t_mtx4 tfm_mtx)
{
	t_mtx3	lin_tfm;

	lin_tfm = mtx3_extract_linear(tfm_mtx);
	mtx3_invert(&lin_tfm);
	lin_tfm = mtx3_transpose(lin_tfm);
	return (lin_tfm);
}

t_vec	gtfm_vec_apply(t_gtfm gtfm, t_vec vec, int tfm)
{
	t_vec4	vec4;
	t_vec4	tmp_res;
	t_vec	res;

	vec4 = vec4_create(vec.x, vec.y, vec.z, 1.0);
	if (tfm == FWD)
	{
		tmp_res = mtx_vec_mult(vec4, gtfm.tfm_mtx);
	}
	else
	{
		tmp_res = mtx_vec_mult(vec4, gtfm.revtfm_mtx);
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

t_vec	apply_lin_tfm(t_gtfm gtfm, t_vec vec)
{
	t_vec	res;

	res = mtx3_vec_mult(vec, gtfm.lin_tfm_mtx);
	return (res);
}
