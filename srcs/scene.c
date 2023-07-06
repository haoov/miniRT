#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

int	scene_render(t_scene *scene, t_img *img)
{
	//Create some material
	t_material	test_mat;
	t_material	test_mat2;
	t_material	test_mat3;
	t_material	floor_material;

	//Set up the material
	test_mat.color = vec_create(0.25, 0.5, 0.8);
	test_mat.reflec = 0.1;
	test_mat.shiny = 10.0;
	test_mat.max_ref_ray = 3;
	test_mat.ref_ray_count = 0;

	test_mat2.color = vec_create(1.0, 0.5, 0.0);
	test_mat2.reflec = 0.75;
	test_mat2.shiny = 10.0;
	test_mat2.max_ref_ray = 3;
	test_mat2.ref_ray_count = 0;

	test_mat3.color = vec_create(1.0, 0.8, 0.0);
	test_mat3.reflec = 0.25;
	test_mat3.shiny = 10;
	test_mat3.max_ref_ray = 3;
	test_mat3.ref_ray_count = 0;

	floor_material.color = vec_create(1.0, 1.0, 1.0);
	floor_material.reflec = 0.5;
	floor_material.shiny = 0.0;
	floor_material.max_ref_ray = 3;
	floor_material.ref_ray_count = 0;

    //Configure the camera
    cam_init(&scene->cam);
    cam_set_pos(&scene->cam, vec_create(0.0, -10.0, -2.0));
    cam_set_look_at(&scene->cam, vec_create(0.0, 0.0, 0.0));
    cam_set_up(&scene->cam, vec_create(0.0, 0.0, 1.0));
    cam_set_size(&scene->cam, 0.25);
    cam_set_ratio(&scene->cam, 16.0 / 9.0);
    cam_geometry(&scene->cam);

	//Create test sphere
	if (add_obj(&scene->obj_lst, SPHERE) == NULL)
	{
		return (FAILURE);
	}
	if (add_obj(&scene->obj_lst, SPHERE) == NULL)
	{
		return (FAILURE);
	}
	if (add_obj(&scene->obj_lst, SPHERE) == NULL)
	{
		return (FAILURE);
	}

	//Modify the sphere
	gtfm_set_transform(vec_create(-1.5, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.5, 0.5, 0.5),
					   &scene->obj_lst->obj.gtfm);
	scene->obj_lst->obj.color = vec_create(0.25, 0.5, 0.8);
	scene->obj_lst->obj.material = test_mat3;
	gtfm_set_transform(vec_create(0.0, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.5, 0.5, 0.5),
					   &obj_lst_at(scene->obj_lst, 1)->obj.gtfm);
	obj_lst_at(scene->obj_lst, 1)->obj.color = vec_create(1.0, 0.5, 0.0);
	obj_lst_at(scene->obj_lst, 1)->obj.material = test_mat;
	gtfm_set_transform(vec_create(1.5, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.5, 0.5, 0.5),
					   &obj_lst_at(scene->obj_lst, 2)->obj.gtfm);
	obj_lst_at(scene->obj_lst, 2)->obj.color = vec_create(1.0, 0.8, 0.0);
	obj_lst_at(scene->obj_lst, 2)->obj.material = test_mat2;

	//Create a test plane
	if (add_obj(&scene->obj_lst, PLANE) == NULL)
	{
		return (FAILURE);
	}

	//Modify the plane
	gtfm_set_transform(vec_create(0.0, 0.0, 0.75),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(4.0, 4.0, 1.0),
					   &obj_lst_at(scene->obj_lst, 3)->obj.gtfm);
	obj_lst_at(scene->obj_lst, 3)->obj.color = vec_create(0.5, 0.5, 0.5);
	obj_lst_at(scene->obj_lst, 3)->obj.material = floor_material;

	//Create test lights
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	scene->light_lst->light.pos = vec_create(5.0, -10.0, -5.0);
	scene->light_lst->light.color = vec_create(0.0, 0.0, 1.0);
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	light_lst_at(scene->light_lst, 1)->light.pos = vec_create(-5.0, -10.0, -5.0);
	light_lst_at(scene->light_lst, 1)->light.color = vec_create(1.0, 0.0, 0.0);
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	light_lst_at(scene->light_lst, 2)->light.pos = vec_create(0.0, -10.0, -5.0);
	light_lst_at(scene->light_lst, 2)->light.color = vec_create(0.0, 1.0, 0.0);

    //Loop over every pixel
    t_ray   	cam_ray;
    double		xfact;
    double		yfact;
    double		xnorm;
    double		ynorm;

    xfact = 1.0 / ((double) img->size_x / 2.0);
    yfact = 1.0 / ((double) img->size_y / 2.0);

    for (int x = 0; x < img->size_x; ++x)
    {
        for (int y = 0; y < img->size_y; ++y)
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
				if (closest_poi.obj->obj.material.type != NONE)
				{
					//Use the material to compute the color
					closest_poi.obj->obj.material.ref_ray_count = 0;
					rgb = compute_color(scene->obj_lst, scene->light_lst,
										closest_poi, cam_ray, closest_poi.obj->obj.material);
				}
				else
				{
					rgb = compute_diffuse_color(scene->obj_lst,
												scene->light_lst, closest_poi,
												closest_poi.obj->obj.color);
/*					//Compute the intensity of illumination
					double intensity;
					t_vec color;
					bool valid_illum = false;
					bool illum_found = false;
					t_light_lst *cur_light;

					rgb = vec_create(0.0, 0.0, 0.0);
					cur_light = scene->light_lst;
					while (cur_light != NULL) {
						valid_illum = point_illum(&closest_poi.point,
												  &closest_poi.normal,
												  &color, &intensity,
												  cur_light->light,
												  scene->obj_lst,
												  closest_poi.obj);
						if (valid_illum) {
							illum_found = true;
							rgb = vec_add(rgb, vec_mult(color, intensity));
						}
						cur_light = cur_light->next;
					}
					if (illum_found) {
						rgb.x *= closest_poi.color.x;
						rgb.y *= closest_poi.color.y;
						rgb.z *= closest_poi.color.z;
						img_store_color(img, x, y, rgb);
					}*/
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
		intersection = obj_cur->obj.intfct(cam_ray, &poi, obj_cur);

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
