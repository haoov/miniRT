#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

int	scene_render(t_app *app, t_scene *scene, t_img *img)
{
	(void)app;
	scene->amb_color = vec_create(1.0, 1.0, 1.0);
	scene->amb_int = 0.2;
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
	t_obj	*cone;
	t_obj	*cylinder;

	plan = plane_create();
	plan->gtfm = gtfm_set(vec_create(0.0, 0.0, 1.0),
						  vec_create(0.0, 0.0, 0.0),
						  vec_create(4.0, 4.0, 1.0));
	sphere = sphere_create();
	sphere->gtfm = gtfm_set(vec_create(-2.0, 0.0, 0.0),
							vec_create(0.0, 0.0, 0.0),
							vec_create(1.0, 1.0, 1.0));
	assign_mat(sphere, mat);
	cone = cone_create();
	cone->gtfm = gtfm_set(vec_create(2.0, 0.0, 0.0),
						  vec_create(180.0, 0.0, 0.0),
						  vec_create(0.5, 0.5, 1.0));
	cylinder = cylinder_create();
	cylinder->gtfm = gtfm_set(vec_create(0.0, 0.0, 0.0),
							  vec_create(0.0, 45.0, 0.0),
							  vec_create(0.5, 0.5, 1.0));

//******************************************************************************
//Add objects to the scene
//******************************************************************************
	add_obj(&scene->obj_lst, plan);
	add_obj(&scene->obj_lst, sphere);
	add_obj(&scene->obj_lst, cone);
	add_obj(&scene->obj_lst, cylinder);

//******************************************************************************
//Create lights
//******************************************************************************
	t_light	*light;
	t_light	*light2;
	t_light	*light3;

	light = new_light();
	light->pos = vec_create(10.0, -5.0, -5.0);
	light->color = vec_create(1.0, 0.0, 0.0);
	add_light(&scene->light_lst, light);
	light2 = new_light();
	light2->pos = vec_create(-10.0, -5.0, -5.0);
	light2->color = vec_create(0.0, 1.0, 0.0);
	add_light(&scene->light_lst, light2);
	light3 = new_light();
	light3->pos = vec_create(0.0, -5.0, -5.0);
	light3->color = vec_create(0.0, 0.0, 1.0);
	add_light(&scene->light_lst, light3);

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
					rgb = diff_color(*scene, poi, poi.obj->color);
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

bool	cast_ray(t_ray cast_ray, t_poi *poi, t_obj *obj_lst, t_obj *obj_cur)
{
	t_poi	test;
	bool	int_found;
	double	dist;
	double	min_dist;

	min_dist = 1e6;
	int_found = false;
	while (obj_lst != NULL)
	{
		if (obj_lst != obj_cur && obj_lst->intfct(cast_ray, &test, obj_lst))
		{
			int_found = true;
			dist = vec_norm(vec_sub(test.point, cast_ray.pa));
			if (dist < min_dist)
			{
				min_dist = dist;
				*poi = test;
			}
		}
		obj_lst = obj_lst->next;
	}
	return (int_found);
}
