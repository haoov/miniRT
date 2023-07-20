/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:42:05 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 09:42:06 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include "mlx_app.h"

uint32_t	img_convert_color(double r, double g, double b, double max)
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	uint32_t		color;

	red = (uint8_t)((r / max) * 255.0);
	green = (uint8_t)((g / max) * 255.0);
	blue = (uint8_t)((b / max) * 255.0);
	color = (0 << 24) + (red << 16) + (green << 8) + blue;
	return (color);
}

void	img_store_color(t_img *img, int x, int y, t_vec rgb)
{
	int	pos;

	pos = y * img->size_x + x;
	img->colors[pos] = rgb;
	if (rgb.x > img->max_rgb)
		img->max_rgb = rgb.x;
	if (rgb.y > img->max_rgb)
		img->max_rgb = rgb.y;
	if (rgb.z > img->max_rgb)
		img->max_rgb = rgb.z;
}

void	img_extract_rgb(t_img img, int index, t_vec *rgb)
{
	uint32_t	*color;

	color = (uint32_t *)(img.data + index);
	if (img.bpp != 32)
	{
		*color = mlx_get_color_value(img.dsp_id, (int) *color);
	}
	if (img.ed == 0)
	{
		rgb->x = (*color >> 16) / 255.0;
		rgb->y = ((*color >> 8) & 0xFF) / 255.0;
		rgb->z = ((*color) & 0xFF) / 255.0;
	}
	else
	{
		rgb->x = ((*color >> 8) & 0xFF) / 255.0;
		rgb->y = ((*color >> 16) & 0xFF) / 255.0;
		rgb->z = ((*color >> 24) & 0xFF) / 255.0;
	}
}
