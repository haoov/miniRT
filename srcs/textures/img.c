#include "texture.h"
#include "object.h"
#include "mlx_app.h"
#include "mlx_image.h"
#include "miniRT.h"

t_texture	img_txt_create(void)
{
	t_texture	img;

	ft_memset(&img, 0, sizeof (t_texture));
	img.colorfct = img_get_color;
	return (img);
}

t_vec	img_get_color(t_texture texture, double u, double v)
{
	t_vec	color;
	t_vec	uv_coords;
	t_vec	new_loc;

	uv_coords.x = u;
	uv_coords.y = v;
	uv_coords.z = 0.0;
	new_loc = apply_transform(texture.tfm, uv_coords);

	double	new_u = new_loc.x;
	double	new_v = new_loc.y;

	//Convert u and v to image dimension
	int	x;
	int	y;
	x = (int) (round(((new_u + 1.0) / 2.0) * (double) texture.img.size_x));
	y = texture.img.size_y - ((int) (round(((new_v + 1.0) / 2.0) * (double) texture.img.size_y)));

	x = ((x % texture.img.size_x) + texture.img.size_x) % texture.img.size_x;
	y = ((y % texture.img.size_y) + texture.img.size_y) % texture.img.size_y;

	int	pixel_index;

	pixel_index = y * texture.img.bpl + x * (texture.img.bpp / 8);

	img_extract_rgb(texture.img, pixel_index, &color);

	return (color);
}

int	load_image(t_app *app, t_texture *texture, char *file_name)
{
	int	width;
	int	height;

	if (texture->img.id != NULL)
		img_destroy(&texture->img);
	texture->img.id = mlx_xpm_file_to_image(app->dsp_id, file_name,
										 &width, &height);
	if (texture->img.id == NULL)
		return (FAILURE);
	texture->img.data = mlx_get_data_addr(texture->img.id, &texture->img.bpp,
										  &texture->img.bpl, &texture->img.ed);
	texture->img.size_x = width;
	texture->img.size_y = height;
	texture->img.dsp_id = app->dsp_id;
	return (SUCCESS);
}
