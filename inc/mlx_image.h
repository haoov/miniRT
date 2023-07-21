/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:22:30 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:22:54 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IMAGE_H
# define MLX_IMAGE_H

# include "libft.h"
# include "vector.h"
# include <inttypes.h>

# define RMASK	0xFF000000
# define GMASK	0xFF0000
# define BMASK	0xFF00

typedef struct s_app	t_app;

typedef struct s_img
{
	void	*id;
	char	*data;
	t_vec	*colors;
	double	max_rgb;
	int		bpp;
	int		ed;
	int		size_x;
	int		size_y;
	int		bpl;
	void	*dsp_id;
}t_img;

t_img		*img_create(void);
int			img_init(t_img *img, void *dsp_id, int size_x, int size_y);
void		img_store_color(t_img *img, int x, int y, t_vec rgb);
uint32_t	img_convert_color(double r, double g, double b, double max);
void		img_set_pixel(t_img *img, int x, int y, uint32_t color);
void		img_display(void *win_id, t_img *img, int x, int y);
void		img_destroy(t_img *img);

#endif
