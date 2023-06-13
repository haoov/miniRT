#ifndef SCENE_H
# define SCENE_H

# include "mlx_image.h"
# include "camera.h"
# include "object.h"

typedef struct s_scene
{
    t_cam   cam;
    t_obj   obj;
}t_scene;

int	scene_render(t_scene *scene, t_img *img);

#endif //SCENE_H
