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
	//Build the transform matrix
	t_mtx3	mtx_rot;
	mtx3_identity(&mtx_rot);
	mtx_rot.val[0][0] = cos(rot);
	mtx_rot.val[0][1] = -sin(rot);
	mtx_rot.val[1][0] = sin(rot);
	mtx_rot.val[1][1] = cos(rot);

	t_mtx3	mtx_scale;
	mtx3_identity(&mtx_scale);
	mtx_scale.val[0][0] = scale.x;
	mtx_scale.val[1][1] = scale.y;

	t_mtx3	mtx_trans;
	mtx3_identity(&mtx_trans);
	mtx_trans.val[0][2] = trans.x;
	mtx_trans.val[1][2] = trans.y;

	//Combine to form the final transform matrix
	t_mtx3	mtx_final;
	mtx_final = mtx3_mult(mtx_trans, mtx_rot);
	mtx_final = mtx3_mult(mtx_final, mtx_scale);
	return (mtx_final);
}

t_vec	blend_colors(t_vec4 input_color)
{
	t_vec	output_color;

	(void)input_color;
	output_color = vec_create(0.0, 0.0, 0.0);
	return (output_color);
}

t_vec	apply_transform(t_mtx3 tfm_mtx, t_vec input_vec)
{
	t_vec	new_input;

	new_input.x = input_vec.x;
	new_input.y = input_vec.y;
	new_input.z = 0.0;

	//Apply the transform
	t_vec	res;
	res = mtx3_vec_mult(new_input, tfm_mtx);

	return (res);
}
