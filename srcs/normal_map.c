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

void	assign_normal_map(t_material *mat, t_normal_map map)
{
	mat->normal_map = map;
	mat->has_normal_map = true;
}

t_vec	nmap_compute_perturb(t_normal_map map,t_vec normal, double u, double v)
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
/*	new_u = fmod(new_u, 1.0);
	new_v = fmod(new_v, 1.0);

	double	xsd = (double) map.img.size_x;
	double	ysd = (double) map.img.size_y;
	double	xF = ((new_u + 1.0) / 2.0) * xsd;
	double	yF = ysd - (((new_v + 1.0) / 2.0) * ysd);
	int		x = (int) round(xF);
	int		y = (int) round(yF);
	(void)x;
	(void)y;
	int		xmin = (int) floor(xF);
	int		ymin = (int) floor(yF);
	int		xmax = (int) ceil(xF);
	int		ymax = (int) ceil(yF);

	//Bilinear interpolation
	t_vec	rgb0;
	t_vec	rgb1;
	t_vec	rgb2;
	t_vec	rgb3;*/

	int	x;
	int	y;
	x = (int) (round(((new_u + 1.0) / 2.0) * (double) map.img.size_x));
	y = map.img.size_y - ((int) (round(((new_v + 1.0) / 2.0) * (double) map.img.size_y)));

	x = ((x % map.img.size_x) + map.img.size_x) % map.img.size_x;
	y = ((y % map.img.size_y) + map.img.size_y) % map.img.size_y;

/*	rgb0 = nmap_extract_rgb(map.img, xmin, ymin);
	rgb1 = nmap_extract_rgb(map.img, xmax, ymin);
	rgb2 = nmap_extract_rgb(map.img, xmin, ymax);
	rgb3 = nmap_extract_rgb(map.img, xmax, ymax);*/

/*	double	interpr;
	double	interpg;
	double	interpb;*/


/*	interpr = bilinear_interp(xmin, ymin, rgb0.x, xmax, ymin, rgb1.x,
							  xmin, ymax, rgb2.x, xmax, ymax, rgb3.x, xF, yF);
	interpg = bilinear_interp(xmin, ymin, rgb0.y, xmax, ymin, rgb1.y,
							  xmin, ymax, rgb2.y, xmax, ymax, rgb3.y, xF, yF);
	interpb = bilinear_interp(xmin, ymin, rgb0.z, xmax, ymin, rgb1.z,
							  xmin, ymax, rgb2.z, xmax, ymax, rgb3.z, xF, yF);*/

/*	t_vec	perturbation = vec_create(interpr, interpg, interpb);*/
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

/*double	linear_interp(double x0, double y0, double x1, double y1, double x)
{
	double	res;

	if ((x1 - x0) == 0.0)
		return (y0);
	else
		res = y0 + ((x - x0) * ((y1 - y0) / (x1 - x0)));
	return (res);
}

double	bilinear_interp(double x0, double y0, double v0,
						double x1, double y1, double v1,
						double x2, double y2, double v2,
						double x3, double y3, double v3,
						double x, double y)
{
	double	p1;
	double	p2;
	double	p3;
	(void)y1;
	(void)y3;

	p1 = linear_interp(x0, v0, x1, v1, x);
	p2 = linear_interp(x2, v2, x3, v3, x);
	p3 = linear_interp(y0, p1, y2, p2, y);
	return (p3);
}*/

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




























