# include "material.h"
#include "object.h"
#include "mlx.h"
#include "miniRT.h"
#include "mlx_app.h"
#include "normal_map.h"

t_normal_map	normal_map_create()
{
	t_normal_map	map;

	ft_memset(&map, 0, sizeof (t_normal_map));
	return (map);
}

void	assign_nmap(t_material *mat, t_normal_map map)
{
	mat->nmap = map;
	mat->has_nmap = true;
}

t_vec	nmap_apply(t_normal_map map, t_vec normal, double u, double v)
{
	//Apply the local transform to the u v coord
	t_vec	uv_coord;
	t_vec	new_loc;

	uv_coord.x = u;
	uv_coord.y = v;
	uv_coord.z = 0.0;
	new_loc = apply_transform(map.tfm, uv_coord);

	double	new_u;
	double	new_v;

	new_u = new_loc.x;
	new_v = new_loc.y;

	int	x;
	int	y;
	x = (int) (round(((new_u + 1.0) / 2.0) * (double) map.img.size_x));
	y = map.img.size_y - ((int) (round(((new_v + 1.0) / 2.0) * (double) map.img.size_y)));

	x = ((x % map.img.size_x) + map.img.size_x) % map.img.size_x;
	y = ((y % map.img.size_y) + map.img.size_y) % map.img.size_y;

	int		pixel_index = y * map.img.bpl + x * (map.img.bpp / 8);
	t_vec	rgb;

	rgb = nmap_extract_rgb(map.img, pixel_index);

	return (perturb_normal(normal, rgb));
}

int	nmap_load_image(t_app *app, t_normal_map *map, char *file_name)
{
	int	width;
	int	height;

	if (map->img.id != NULL)
		img_destroy(&map->img);
	map->img.id = mlx_xpm_file_to_image(app->dsp_id, file_name,
											&width, &height);
	if (map->img.id == NULL)
		return (FAILURE);
	map->img.data = mlx_get_data_addr(map->img.id, &map->img.bpp,
										  &map->img.bpl, &map->img.ed);
	map->img.size_x = width;
	map->img.size_y = height;
	map->img.dsp_id = app->dsp_id;
	return (SUCCESS);
}

t_vec	nmap_extract_rgb(t_img img, int pixel_index)
{
	t_vec	rgb;

	uint32_t *color;

	color = (uint32_t *) (img.data + pixel_index);
	if (img.bpp != 32)
	{
		*color = mlx_get_color_value(img.dsp_id, (int) *color);
	}
	if (img.ed == 0)
	{
		rgb.x = ((double) (*color >> 16) - 128.0) / 128.0;
		rgb.y = ((double) ((*color >> 8) & 0xFF) - 128.0) / 128.0;
		rgb.z = (double) ((*color) & 0xFF) / 255.0;
	}
	else
	{
		rgb.x = (double) ((*color >> 8) & 0xFF);
		rgb.y = (double) ((*color >> 16) & 0xFF);
		rgb.z = (double) ((*color >> 24) & 0xFF);
	}
	return (rgb);
}

t_vec	perturb_normal(t_vec normal, t_vec perturbation)
{
	t_vec	up_vec;

	up_vec = vec_create(0.0, 0.0, -1.0);
	if (normal.z > 0.99 || normal.z < -0.99)
		up_vec = vec_create(1.0, 0.0, 0.0);

	t_vec	pv;
	t_vec	pu;

	pv = vec_cross(up_vec, normal);
	vec_normalize(&pv);
	pu = vec_cross(normal, pv);
	vec_normalize(&pu);

	t_vec	output;

	output = vec_add(normal, vec_mult(pu, perturbation.x));
	output = vec_add(output, vec_mult(pv, perturbation.y));
	output = vec_add(output, vec_mult(normal, perturbation.z));
	vec_normalize(&output);

	return (output);
}




























