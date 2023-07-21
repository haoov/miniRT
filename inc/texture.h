/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:35:56 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:37:11 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "matrix.h"
# include "vector.h"
# include "ray.h"
# include "mlx_image.h"

typedef struct s_texture
{
	t_vec4	color1;
	t_vec4	color2;
	t_img	img;
	t_vec	(*colorfct)(struct s_texture, double, double);
	t_mtx3	tfm;
}t_texture;

t_mtx3		set_transform(t_vec trans, double rot, t_vec scale);
t_vec		blend_colors(t_vec4 input_color);
t_vec		apply_transform(t_mtx3 tfm_mtx, t_vec input_vec);

t_texture	create_flat_texture(void);
t_texture	create_checker_texture(void);
t_texture	img_txt_create(void);

t_vec		flat_get_color(t_texture texture, double u, double v);
t_vec		checker_get_color(t_texture texture, double u, double v);
t_vec		img_get_color(t_texture texture, double u, double v);

int			load_image(t_app *app, t_texture *texture, char *file_name);
void		img_extract_rgb(t_img img, int index, t_vec *rgb);

#endif
