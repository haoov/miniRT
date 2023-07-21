/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm_mtx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:42:28 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 10:42:29 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtfm.h"

t_mtx4	trans_mtx(t_vec trans)
{
	t_mtx4	trans_mtx;

	mtx4_identity(&trans_mtx);
	trans_mtx.val[0][3] = trans.x;
	trans_mtx.val[1][3] = trans.y;
	trans_mtx.val[2][3] = trans.z;
	return (trans_mtx);
}

t_mtx4	scale_mtx(t_vec scale)
{
	t_mtx4	scale_mtx;

	mtx4_identity(&scale_mtx);
	scale_mtx.val[0][0] = scale.x;
	scale_mtx.val[1][1] = scale.y;
	scale_mtx.val[2][2] = scale.z;
	return (scale_mtx);
}

t_mtx4	rotx_mtx(t_vec rot)
{
	t_mtx4	rotx_mtx;

	mtx4_identity(&rotx_mtx);
	rotx_mtx.val[1][1] = cos(rot.x);
	rotx_mtx.val[1][2] = -sin(rot.x);
	rotx_mtx.val[2][1] = sin(rot.x);
	rotx_mtx.val[2][2] = cos(rot.x);
	return (rotx_mtx);
}

t_mtx4	roty_mtx(t_vec rot)
{
	t_mtx4	roty_mtx;

	mtx4_identity(&roty_mtx);
	roty_mtx.val[0][0] = cos(rot.y);
	roty_mtx.val[0][2] = sin(rot.y);
	roty_mtx.val[2][0] = -sin(rot.y);
	roty_mtx.val[2][2] = cos(rot.y);
	return (roty_mtx);
}

t_mtx4	rotz_mtx(t_vec rot)
{
	t_mtx4	rotz_mtx;

	mtx4_identity(&rotz_mtx);
	rotz_mtx.val[0][0] = cos(rot.z);
	rotz_mtx.val[0][1] = -sin(rot.z);
	rotz_mtx.val[1][0] = sin(rot.z);
	rotz_mtx.val[1][1] = cos(rot.z);
	return (rotz_mtx);
}
