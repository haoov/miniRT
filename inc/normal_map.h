/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:22:58 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:23:05 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_MAP_H
# define NORMAL_MAP_H

# include "mlx_image.h"

typedef struct s_normal_map
{
	t_img	img;
	t_mtx3	tfm;
}t_normal_map;

t_vec			nmap_extract_rgb(t_img img, int pixel_index);
t_vec			perturb_normal(t_vec normal, t_vec perturbation);
t_vec			nmap_apply(t_normal_map map, t_vec normal, double u, double v);
t_normal_map	normal_map_create(void);
int				nmap_load_image(t_app *app, t_normal_map *map, char *file_name);

#endif
