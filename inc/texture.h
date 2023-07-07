#ifndef TEXTURE_H
# define TEXTURE_H

# include "matrix.h"
# include "vector.h"
# include "ray.h"

typedef struct s_texture
{
	t_vec4	color1;
	t_vec4	color2;
	t_img	img;
	int		img_width;
	int		img_height;
	t_vec	(*colorfct)(struct s_texture, double, double);
	t_mtx3	tfm;
}t_texture;

t_mtx3	set_transform(t_vec trans, double rot, t_vec scale);
t_vec	blend_colors(t_vec4 input_color);
t_vec	apply_transform(t_mtx3 tfm_mtx, t_vec input_vec);

t_texture	create_flat_texture(void);
t_texture	create_checker_texture(void);

t_vec	flat_get_color(t_texture texture, double u, double v);
t_vec	checker_get_color(t_texture texture, double u, double v);

#endif
