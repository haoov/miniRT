/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:59:45 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:59:46 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "object.h"
#include <math.h>

void	assign_texture(t_material *material, t_texture texture)
{
	material->texture = texture;
	material->has_texture = true;
}

t_mtx3	set_transform(t_vec trans, double rot, t_vec scale)
{
	t_mtx3	mtx_rot;
	t_mtx3	mtx_scale;
	t_mtx3	mtx_trans;
	t_mtx3	mtx_final;

	mtx3_identity(&mtx_rot);
	mtx_rot.val[0][0] = cos(rot);
	mtx_rot.val[0][1] = -sin(rot);
	mtx_rot.val[1][0] = sin(rot);
	mtx_rot.val[1][1] = cos(rot);
	mtx3_identity(&mtx_scale);
	mtx_scale.val[0][0] = scale.x;
	mtx_scale.val[1][1] = scale.y;
	mtx3_identity(&mtx_trans);
	mtx_trans.val[0][2] = trans.x;
	mtx_trans.val[1][2] = trans.y;
	mtx_final = mtx3_mult(mtx_trans, mtx_rot);
	mtx_final = mtx3_mult(mtx_final, mtx_scale);
	return (mtx_final);
}

t_vec	apply_transform(t_mtx3 tfm_mtx, t_vec input_vec)
{
	t_vec	new_input;
	t_vec	res;

	new_input.x = input_vec.x;
	new_input.y = input_vec.y;
	new_input.z = 0.0;
	res = mtx3_vec_mult(new_input, tfm_mtx);
	return (res);
}
