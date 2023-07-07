#include "texture.h"
#include "object.h"
#include "mlx_app.h"
#include "mlx_image.h"
#include "miniRT.h"

t_texture	img_txt_create(void)
{

}

t_vec	img_get_color(t_texture texture, double u, double v)
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

	//Convert u and v to image dimension
	int	x;
	int	y;
	x = (int) (round(((u + 1.0) / 2.0) * (double) texture.img.size_x));
	y = texture.img.size_y - ((int) (round(((v + 1.0) / 2.0) * (double) texture.img.size_y)));

	x = ((x % texture.img.size_x) + texture.img.size_x) % texture.img.size_x;
	y = ((y % texture.img.size_y) + texture.img.size_y) % texture.img.size_y;

	int	pixel_index;
}

int	load_image(t_app *app, t_texture *texture, char *file_name)
{
	int	width;
	int	height;

	if (texture->img.id != NULL)
		img_destroy(&texture->img);
	texture->img.id = mlx_xpm_file_to_image(app->dsp_id, file_name,
										 &width, &height);
	if (texture->img == NULL)
		return (FAILURE);
	texture->img.data = mlx_get_data_addr(texture->img.id, &texture->img.bbp,
										  texture->img.bpl, &texture->img.ed);
	texture->img.size_x = width;
	texture->img.size_y = height;
	return (SUCCESS);
}
