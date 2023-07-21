/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:17:17 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 10:18:23 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "object.h"
#include "mlx_app.h"
#include "mlx_image.h"
#include "miniRT.h"

#include "stdio.h"

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
	t_vec	new_loc;
	int		x;
	int		y;
	int		pixel_index;

	new_loc = apply_transform(texture.tfm, vec_create(u, v, 0.0));
	x = (int)(round(((new_loc.x + 1.0) / 2.0) * (double) texture.img.size_x));
	y = texture.img.size_y - ((int)(round(((new_loc.y + 1.0) / 2.0)
					* (double) texture.img.size_y)));
	x = ((x % texture.img.size_x) + texture.img.size_x) % texture.img.size_x;
	y = ((y % texture.img.size_y) + texture.img.size_y) % texture.img.size_y;
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
