#ifndef SCENE_H
# define SCENE_H

# include "mlx_image.h"
# include "camera.h"
# include "object.h"
# include "light.h"
# include "material.h"

typedef struct s_scene
{
    t_cam   cam;
    t_obj   *obj_lst;
	t_light	*light_lst;
	t_vec	amb_color;
	double	amb_int;
}t_scene;

int	scene_render(t_app *app, t_scene *scene, t_img *img);
bool	s_cast_ray(t_ray cam_ray, t_poi *closest_poi, t_obj *obj_cur);

#endif //SCENE_H
