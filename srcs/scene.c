#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

int	scene_render(t_app *app, t_scene *scene, t_img *img)
{
	(void)app;
	scene->amb_int = 0.0;
//******************************************************************************
//Create some mat
//******************************************************************************
	t_material	mat;

	mat = simple_mat_const(vec_create(0.0, 0.0, 1.0), 0.5, 5.0);
	(void)mat;

//******************************************************************************
//Create some textures
//******************************************************************************


//******************************************************************************
//Create normal map
//******************************************************************************


//******************************************************************************
//Configure the camera
//******************************************************************************
    cam_init(&scene->cam);
	scene->cam.pos = vec_create(0.0, -5.0, -2.0);
	scene->cam.look_at = vec_create(0.0, 0.0, 0.0);
	scene->cam.up = vec_create(0.0, 0.0, 1.0);
	scene->cam.size = 0.75;
	scene->cam.ratio = 16.0 / 9.0;
    cam_geometry(&scene->cam);

//******************************************************************************
//Create some objects
//******************************************************************************
	t_obj	*plan;
	t_obj	*sphere;

	plan = plane_create();
	plan->color = vec_create(1.0, 0.0, 0.0);
	plan->gtfm = gtfm_set(vec_create(0.0, 0.0, 1.0),
						  vec_create(0.0, 0.0, 0.0),
						  vec_create(4.0, 4.0, 1.0));
	sphere = sphere_create();
	sphere->gtfm = gtfm_set(vec_create(0.0, 0.0, 0.0),
							vec_create(0.0, 0.0, 0.0),
							vec_create(1.0, 1.0, 1.0));
	assign_material(sphere, mat);

//******************************************************************************
//Add objects to the scene
//******************************************************************************
	add_obj(&scene->obj_lst, plan);
	add_obj(&scene->obj_lst, sphere);

//******************************************************************************
//Create lights
//******************************************************************************
	t_light	*light;

	light = new_light();
	light->pos = vec_create(5.0, -10.0, -5.0);
	add_light(&scene->light_lst, light);

    //Loop over every pixel
    t_ray   	cam_ray;
    double		xfact;
    double		yfact;
    double		xnorm;
    double		ynorm;

    xfact = 1.0 / ((double) img->size_x / 2.0);
    yfact = 1.0 / ((double) img->size_y / 2.0);

    for (int y = 0; y < img->size_y; ++y)
    {
		printf("Processing row %d of %d\r\033[0K", y + 1, img->size_y);
        for (int x = 0; x < img->size_x; ++x)
        {
            //Normalize x and y coordinates
            xnorm = (float) x * xfact - 1.0;
            ynorm = (float) y * yfact - 1.0;

            //generate the ray
            cam_ray = cam_generate_ray(&scene->cam, (float) xnorm, (float) ynorm);

			//Loop on every object in the scene
			t_poi	poi;
			bool	intersection;

			intersection = s_cast_ray(cam_ray, &poi, scene->obj_lst);

			//Compute the illumination for the closest object
			if (intersection)
			{
				t_vec rgb;

				//Check if the object has mat
				if (poi.obj->has_mat)
				{
					//Use the mat to compute the color
					poi.obj->mat.ref_ray_count = 0;
					rgb = poi.obj->mat.colorfct(*scene, cam_ray, poi);
				}
				else
				{
					rgb = compute_diffuse_color(*scene, poi, poi.obj->color);
				}
				img_store_color(img, x, y, rgb);
			}
        }
    }
	return (SUCCESS);
}

bool	s_cast_ray(t_ray cam_ray, t_poi *closest_poi, t_obj *obj_cur)
{
	t_poi	poi;
	bool	intersection;
	bool	int_found;
	double	dist;
	double	min_dist;

	min_dist = 1e6;
	int_found = false;
	while (obj_cur != NULL)
	{
		//Test intersection
		intersection = obj_cur->intfct(cam_ray, &poi, obj_cur);

		if (intersection)
		{
			int_found = true;
			//Compute the distance between the camera and the poi
			dist = vec_norm(vec_sub(poi.point, cam_ray.pa));

			//If this object is closer to the cam than the others
			if (dist < min_dist)
			{
				min_dist = dist;
				*closest_poi = poi;
			}
		}
		obj_cur = obj_cur->next;
	}
	return (int_found);
}
