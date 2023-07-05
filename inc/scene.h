#ifndef SCENE_H
# define SCENE_H

# include "mlx_image.h"
# include "camera.h"
# include "object.h"
# include "light.h"

typedef struct s_scene
{
    t_cam   	cam;
    t_obj_lst   *obj_lst;
	t_light_lst	*light_lst;
}t_scene;

int	scene_render(t_scene *scene, t_img *img);

#endif //SCENE_H
