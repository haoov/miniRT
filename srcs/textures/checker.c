/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:59:57 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 20:23:24 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_texture	create_checker_texture(void)
{
	t_texture	checker;

	ft_memset(&checker, 0, sizeof (t_texture));
	checker.color1 = vec4_create(1.0, 1.0, 1.0, 1.0);
	checker.color2 = vec4_create(0.2, 0.2, 0.2, 1.0);
	checker.colorfct = checker_get_color;
	return (checker);
}

t_vec	checker_get_color(t_texture texture, double u, double v)
{
	t_vec	color;
	t_vec4	color4;
	t_vec	new_loc;
	int		check;

	new_loc = apply_transform(texture.tfm, vec_create(u, v, 0.0));
	check = (int)(floor(new_loc.x)) + (int)(floor(new_loc.y));
	if (check % 2 == 0)
	{
		color4 = texture.color1;
	}
	else
	{
		color4 = texture.color2;
	}
	color.x = color4.x;
	color.y = color4.y;
	color.z = color4.z;
	return (color);
}
