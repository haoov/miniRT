#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

t_light_lst	*add_light(t_light_lst **light_lst, int type);

int	scene_render(t_scene *scene, t_img *img)
{
    //Configure the camera
    cam_init(&scene->cam);
    cam_set_pos(&scene->cam, vec_create(0.0, -10.0, -10.0));
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
					   vec_create(0.5, 0.5, 0.75),
					   &scene->obj_lst->obj.gtfm);
	scene->obj_lst->obj.color = vec_create(64.0, 128.0, 200.0);
	gtfm_set_transform(vec_create(0.0, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.75, 0.5, 0.5),
					   &obj_lst_at(scene->obj_lst, 1)->obj.gtfm);
	obj_lst_at(scene->obj_lst, 1)->obj.color = vec_create(255.0, 128.0, 0.0);
	gtfm_set_transform(vec_create(1.5, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.75, 0.75, 0.75),
					   &obj_lst_at(scene->obj_lst, 2)->obj.gtfm);
	obj_lst_at(scene->obj_lst, 2)->obj.color = vec_create(255.0, 200.0, 0.0);

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
	obj_lst_at(scene->obj_lst, 3)->obj.color = vec_create(128.0, 128.0, 128.0);

	//Create test lights
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	scene->light_lst->light.pos = vec_create(5.0, -10.0, -5.0);
	scene->light_lst->light.color = vec_create(0.0, 0.0, 255.0);
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	light_lst_at(scene->light_lst, 1)->light.pos = vec_create(-5.0, -10.0, -5.0);
	light_lst_at(scene->light_lst, 1)->light.color = vec_create(255.0, 0.0, 0.0);
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	light_lst_at(scene->light_lst, 2)->light.pos = vec_create(0.0, -10.0, -5.0);
	light_lst_at(scene->light_lst, 2)->light.color = vec_create(0.0, 255.0, 0.0);

    //Loop over every pixel
    t_ray   	cam_ray;
    t_vec		int_point;
    t_vec   	local_normal;
    t_vec		local_color;
    double		xfact;
    double		yfact;
    double		xnorm;
    double		ynorm;
    double		min_dist;
    double		max_dist;
    double		dist;
    bool		intersect;

    xfact = 1.0 / ((double) img->size_x / 2.0);
    yfact = 1.0 / ((double) img->size_y / 2.0);
	max_dist = 0.0;

    for (int x = 0; x < img->size_x; ++x)
    {
        for (int y = 0; y < img->size_y; ++y)
        {
			//Set min dist
			min_dist = 1e6;

            //Normalize x and y coordinates
            xnorm = (float) x * xfact - 1.0;
            ynorm = (float) y * yfact - 1.0;

            //generate the ray
            cam_ray = cam_generate_ray(&scene->cam, (float) xnorm, (float) ynorm);

			//Loop on every object in the scene
			t_obj_lst	*cur_obj;
			t_obj_lst	*closest_obj;
			t_vec		closest_int_point;
			t_vec		closest_normal;
			t_vec		closest_color;
			bool		int_found = false;
			cur_obj = scene->obj_lst;
			while (cur_obj != NULL)
			{
				//Test intersection
				intersect = cur_obj->obj.intfct(cam_ray, &int_point, &local_normal, &local_color, cur_obj->obj);

				if (intersect)
				{
					//Set the flag
					int_found = true;

					//Compute the distance between the camera and the poi
					dist = vec_norm(vec_sub(int_point, cam_ray.pa));

					//If this object is closer to the cam than the others
					if (dist < min_dist)
					{
						min_dist = dist;
						closest_obj = cur_obj;
						closest_int_point = int_point;
						closest_normal = local_normal;
						closest_color = local_color;
					}
/*					//Compute the intensity
					double		intensity;
					t_vec		lcolor;
					bool		illum;
					t_light_lst	*lcur;

					lcur = scene->light_lst;
					while (lcur != NULL)
					{
						illum = lcur->light.illumfct(&int_point, &local_normal, &lcolor, &intensity, lcur->light);
						lcur = lcur->next;
					}

					dist = vec_norm(vec_sub(int_point, cam_ray.pa));
					if (dist > max_dist)
					{
						max_dist = dist;
					}
					if (dist < min_dist)
					{
						min_dist = dist;
					}
					if (illum)
					{
						img_set_pixel(img, x, y, img_convert_color(cur_obj->obj.local_color.x * intensity,
																   cur_obj->obj.local_color.y * intensity,
																   cur_obj->obj.local_color.z * intensity));
					}*/
				}
				cur_obj = cur_obj->next;
			}

			//Compute the illumination for the closest object
			if (int_found)
			{
				//Compute the intensity of illumination
				double		intensity;
				t_vec		color;
				t_vec		rgb;
				bool		valid_illum = false;
				bool		illum_found = false;
				t_light_lst	*cur_light;

				rgb = vec_create(0.0, 0.0, 0.0);
				cur_light = scene->light_lst;
				while (cur_light != NULL)
				{
					valid_illum = point_illum(&closest_int_point, &closest_normal,
											  &color, &intensity, cur_light->light,
											  scene->obj_lst, closest_obj);
					if (valid_illum)
					{
						illum_found = true;
						rgb = vec_add(rgb, vec_mult(color, intensity));
					}
					cur_light = cur_light->next;
				}
				if (illum_found)
				{
					rgb.x *= closest_color.x;
					rgb.y *= closest_color.y;
					rgb.z *= closest_color.z;
					img_store_color(img, x, y, rgb);
				}
			}
        }
    }
	return (SUCCESS);
}
