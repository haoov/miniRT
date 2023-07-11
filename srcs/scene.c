#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

int	scene_render(t_app *app, t_scene *scene, t_img *img)
{
	(void)app;
//******************************************************************************
//Create some material
//******************************************************************************
	t_material	bluediff;

	bluediff = simple_mat_const(vec_create(0.2, 0.2, 0.8), 0.0, 0.0);

//******************************************************************************
//Create some textures
//******************************************************************************
	t_texture	water_img;

	water_img = img_txt_create();
	load_image(app, &water_img, "./imgs/Water-0341.xpm");
	water_img.tfm =  set_transform(vec_create(0.0, 0.0, 0.0), 0.0,
								   vec_create(20.0, 20.0, 20.0));
	assign_texture(&bluediff, water_img);

//******************************************************************************
//Create normal map
//******************************************************************************
	t_normal_map	water_map;

	water_map = normal_map_create();
	nmap_load_image(app, &water_map, "./normal_maps/Water-0341normal.xpm");
	water_map.tfm = set_transform(vec_create(0.0, 0.0, 0.0), 0.0,
								  vec_create(20.0, 20.0, 20.0));
	assign_normal_map(&bluediff, water_map);

//******************************************************************************
//Configure the camera
//******************************************************************************
    cam_init(&scene->cam);
	scene->cam.pos = vec_create(0.0, -10.0, -2.0);
	scene->cam.look_at = vec_create(0.0, 0.0, 0.0);
	scene->cam.up = vec_create(0.0, 0.0, 1.0);
	scene->cam.size = 0.5;
	scene->cam.ratio = 16.0 / 9.0;
    cam_geometry(&scene->cam);

//******************************************************************************
//Create some objects
//******************************************************************************
	t_obj_lst	*plane;

	plane = plane_create();
	plane->gtfm = gtfm_set(vec_create(0.0, 0.0, 0.0),
						   vec_create(0.0, 0.0, 0.0),
						   vec_create(20.0, 20.0, 20.0));
	assign_material(plane, bluediff);

//******************************************************************************
//Add objects to the scene
//******************************************************************************
	add_obj(&scene->obj_lst, plane);

//******************************************************************************
//Create lights
//******************************************************************************
	if (add_light(&scene->light_lst, POINT) == NULL)
		return (FAILURE);
	scene->light_lst->light.pos = vec_create(0.0, 0.0, 5.0);
	scene->light_lst->light.color = vec_create(1.0, 1.0, 1.0);

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
			t_poi	closest_poi;
			bool	intersection;

			intersection = s_cast_ray(cam_ray, &closest_poi, scene->obj_lst);

			//Compute the illumination for the closest object
			if (intersection)
			{
				t_vec rgb;

				//Check if the object has material
				if (closest_poi.obj->has_material)
				{
					//Use the material to compute the color
					closest_poi.obj->material.ref_ray_count = 0;
					rgb = closest_poi.obj->material.colorfct(scene->obj_lst, scene->light_lst,
										closest_poi, cam_ray, closest_poi.obj->material);
				}
				else
				{
					rgb = compute_diffuse_color(scene->obj_lst,
												scene->light_lst, closest_poi,
												closest_poi.obj->color);
				}
				img_store_color(img, x, y, rgb);
			}
        }
    }
	return (SUCCESS);
}

bool	s_cast_ray(t_ray cam_ray, t_poi *closest_poi, t_obj_lst *obj_cur)
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
