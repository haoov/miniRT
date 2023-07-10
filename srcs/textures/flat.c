# include "texture.h"

t_texture	create_flat_texture(void)
{
	t_texture	flat;

	ft_memset(&flat, 0, sizeof (t_texture));
	flat.color1 = vec4_create(1.0, 0.0, 0.0, 1.0);
	flat.colorfct = flat_get_color;
	return (flat);
}

t_vec	flat_get_color(t_texture texture, double u, double v)
{
	t_vec	color;

	(void)u;
	(void)v;
	color.x = texture.color1.x;
	color.y = texture.color1.y;
	color.z = texture.color1.z;
	return (color);
}
