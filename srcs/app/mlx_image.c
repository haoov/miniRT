/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:37:31 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 09:39:06 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include "mlx_app.h"
#include "miniRT.h"

#include <stdio.h>

int	img_init(t_img *img, void *dsp_id, int size_x, int size_y)
{
	img->id = mlx_new_image(dsp_id, size_x, size_y);
	if (img->id == NULL)
	{
		return (FAILURE);
	}
	img->data = mlx_get_data_addr(img->id, &img->bpp, &img->bpl, &img->ed);
	if (img->data == NULL)
	{
		return (FAILURE);
	}
	img->colors = (t_vec *) ft_calloc(size_x * size_y, sizeof (t_vec));
	if (img->colors == NULL)
	{
		return (FAILURE);
	}
	img->size_x = size_x;
	img->size_y = size_y;
	img->dsp_id = dsp_id;
	return (SUCCESS);
}

void	img_set_pixel(t_img *img, int x, int y, uint32_t color)
{
	uint32_t	*p_color;

	p_color = (uint32_t *)(img->data + (y * img->bpl) + (x * (img->bpp / 8)));
	if (img->bpp != 32)
		color = mlx_get_color_value(img->dsp_id, (int) color);
	if (img->ed == 0)
	{
		*p_color = color;
	}
	else
	{
		*p_color = ((color & 0xFF) << 24) + (((color >> 8) & 0xFF) << 16)
			+ (((color >> 16) & 0xFF) << 8) + ((color >> 24) & 0xFF);
	}
}

void	img_display(void *win_id, t_img *img, int x, int y)
{
	int			i;
	int			j;
	int			pos;
	uint32_t	color;

	i = 0;
	while (i < img->size_x)
	{
		j = 0;
		while (j < img->size_y)
		{
			pos = j * img->size_x + i;
			color = img_convert_color(img->colors[pos].x,
					img->colors[pos].y,
					img->colors[pos].z, img->max_rgb);
			img_set_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->dsp_id, win_id, img->id, x, y);
}

void	img_destroy(t_img *img)
{
	if (img->id != NULL)
	{
		mlx_destroy_image(img->dsp_id, img->id);
		if (img->colors != NULL)
		{
			free(img->colors);
		}
	}
}
