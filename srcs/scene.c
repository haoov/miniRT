#include "scene.h"
#include "miniRT.h"

int	scene_render(t_img *img)
{
	int		x;
	int 	y;
	double	red;
	double	green;

	x = 0;
	while (x < img->size_x)
	{
		y = 0;
		while (y < img->size_y)
		{
			red = (double) (x / 1280.0) * 255.0;
			green = (double) (y / 720.0) * 255.0;
			img_set_pixel(img, x, y, img_convert_color(red, green, 0.0));
			++y;
		}
		++x;
	}
	return (SUCCESS);
}
