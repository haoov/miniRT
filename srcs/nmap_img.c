/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmap_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:17:10 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:17:49 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "object.h"
#include "miniRT.h"
#include "mlx_app.h"
#include "normal_map.h"

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
	t_vec		rgb;
	uint32_t	*color;

	color = (uint32_t *)(img.data + pixel_index);
	if (img.bpp != 32)
	{
		*color = mlx_get_color_value(img.dsp_id, (int) *color);
	}
	if (img.ed == 0)
	{
		rgb.x = ((double)(*color >> 16) - 128.0) / 128.0;
		rgb.y = ((double)((*color >> 8) & 0xFF) - 128.0) / 128.0;
		rgb.z = (double)((*color) & 0xFF) / 255.0;
	}
	else
	{
		rgb.x = (double)((*color >> 8) & 0xFF);
		rgb.y = (double)((*color >> 16) & 0xFF);
		rgb.z = (double)((*color >> 24) & 0xFF);
	}
	return (rgb);
}
