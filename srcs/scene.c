#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

int	scene_render(t_scene *scene, t_img *img)
{
    //Configure the camera
    cam_init(&scene->cam);
    cam_set_pos(&scene->cam, vec_create(0.0, -10.0, 0.0));
    cam_set_look_at(&scene->cam, vec_create(0.0, 0.0, 0.0));
    cam_set_up(&scene->cam, vec_create(0.0, 0.0, 1.0));
    cam_set_size(&scene->cam, 0.25);
    cam_set_ratio(&scene->cam, 16.0 / 9.0);
    cam_geometry(&scene->cam);

    //Loop over every pixel
    t_ray   cam_ray;
    t_vec   point;
    t_vec   normal;
    t_vec   color;
    double  xfact;
    double  yfact;
    double  xnorm;
    double  ynorm;
    double  mindist;
    double  maxdist;
    double  dist;
    bool    intersect;

    xfact = 1.0 / ((double) img->size_x / 2.0);
    yfact = 1.0 / ((double) img->size_y / 2.0);
    mindist = 1e6;
    maxdist = 0.0;

    for (int x = 0; x < img->size_x; ++x)
    {
        for (int y = 0; y < img->size_y; ++y)
        {
            //Normalize x and y coordinates
            xnorm = (float) x * xfact - 1.0;
            ynorm = (float) y * yfact - 1.0;

            //generate the ray
            cam_ray = cam_generate_ray(&scene->cam, (float) xnorm, (float) ynorm);

            //Test intersection
            intersect = sphere_intersect(cam_ray, &point, &normal, &color);

            if (intersect)
            {
                dist = vec_norm(vec_sub(point, cam_ray.pa));
                if (dist > maxdist)
                {
                    maxdist = dist;
                }
                if (dist < mindist)
                {
                    mindist = dist;
                }
                img_set_pixel(img, x, y, img_convert_color(255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0));
            }
        }
    }

	return (SUCCESS);
}
