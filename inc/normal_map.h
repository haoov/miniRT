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
t_normal_map	normal_map_create();
int				nmap_load_image(t_app *app, t_normal_map *map, char *file_name);

#endif
