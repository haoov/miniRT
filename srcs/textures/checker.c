#include "texture.h"

#include <stdio.h>

t_texture	create_checker_texture(void)
{
	t_texture	checker;

	ft_memset(&checker, 0, sizeof (t_texture));
	checker.color1 = vec4_create(1.0, 1.0, 1.0, 1.0);
	checker.color2 = vec4_create(0.2, 0.2, 0.2, 1.0);
	checker.colorfct = checker_get_color;
	return (checker);
}

t_vec	checker_get_color(t_texture texture, double u, double v)
{
	t_vec	color;
	t_vec4	color4;
	t_vec	uv_coords;
	t_vec	new_loc;

	uv_coords.x = u;
	uv_coords.y = v;
	new_loc = apply_transform(texture.tfm, uv_coords);

	double	new_u = new_loc.x;
	double	new_v = new_loc.y;

	int	check = (int) (floor(new_u)) + (int) (floor(new_v));

	if (check % 2 == 0)
	{
		color4 = texture.color1;
	}
	else
	{
		color4 = texture.color2;
	}
	color.x = color4.x;
	color.y = color4.y;
	color.z = color4.z;
	return (color);
}
