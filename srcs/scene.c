#include "scene.h"
#include "miniRT.h"

#include <stdio.h>

t_obj_lst	*add_obj(t_obj_lst **obj_lst, int type);
t_light_lst	*add_light(t_light_lst **light_lst, int type);

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
	gtfm_set_transform(vec_create(-1, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.5, 0.5, 0.75),
					   &scene->obj_lst->obj.gtfm);
	scene->obj_lst->obj.color = vec_create(64.0, 128.0, 200.0);
	gtfm_set_transform(vec_create(0.0, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.75, 0.5, 0.5),
					   &scene->obj_lst->next->obj.gtfm);
	scene->obj_lst->next->obj.color = vec_create(255.0, 128.0, 0.0);
	gtfm_set_transform(vec_create(1, 0.0, 0.0),
					   vec_create(0.0, 0.0, 0.0),
					   vec_create(0.75, 0.75, 0.75),
					   &scene->obj_lst->next->next->obj.gtfm);
	scene->obj_lst->next->next->obj.color = vec_create(255.0, 200.0, 0.0);

	//Create a test light
	if (add_light(&scene->light_lst, POINT) == NULL)
	{
		return (FAILURE);
	}
	scene->light_lst->light.pos = vec_create(5.0, -10.0, -5.0);

    //Loop over every pixel
    t_ray   	cam_ray;
    t_vec		point;
    t_vec   	normal;
    t_vec		color;
    double		xfact;
    double		yfact;
    double		xnorm;
    double		ynorm;
    double		mindist;
    double		maxdist;
    double		dist;
    bool		intersect;

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

			//Loop on every object in the scene
			t_obj_lst	*cur;
			cur = scene->obj_lst;
			while (cur != NULL)
			{
				//Test intersection
				intersect = cur->obj.intfct(cam_ray, &point, &normal, &color, cur->obj);

				if (intersect)
				{
					//Compute the intensity
					double		intensity;
					t_vec		lcolor;
					bool		illum;
					t_light_lst	*lcur;

					lcur = scene->light_lst;
					while (lcur != NULL)
					{
						illum = lcur->light.illumfct(&point, &normal, &lcolor, &intensity, lcur->light);
						lcur = lcur->next;
					}

					dist = vec_norm(vec_sub(point, cam_ray.pa));
					if (dist > maxdist)
					{
						maxdist = dist;
					}
					if (dist < mindist)
					{
						mindist = dist;
					}
					if (illum)
					{
						img_set_pixel(img, x, y, img_convert_color(cur->obj.color.x * intensity,
																   cur->obj.color.y * intensity,
																   cur->obj.color.z * intensity));
					}
				}
				cur = cur->next;
			}
        }
    }
	return (SUCCESS);
}

t_obj_lst	*add_obj(t_obj_lst **obj_lst, int type)
{
	t_obj_lst	*new;
	t_obj_lst	*elem;

	new = (t_obj_lst *) ft_calloc(1, sizeof (t_obj_lst));
	if (new == NULL)
	{
		return (NULL);
	}
	if (type == SPHERE)
	{
		new->obj.intfct = sphere_intersect;
	}
	if (*obj_lst == NULL)
	{
		*obj_lst = new;
	}
	else
	{
		elem = *obj_lst;
		while (elem->next != NULL)
		{
			elem = elem->next;
		}
		elem->next = new;
	}
	return (*obj_lst);
}

t_light_lst	*add_light(t_light_lst **light_lst, int type)
{
	t_light_lst	*new;
	t_light_lst	*elem;

	new = (t_light_lst *) ft_calloc(1, sizeof (t_light_lst));
	if (new == NULL)
	{
		return (NULL);
	}
	new->light.intensity = 1.0;
	new->light.color = vec_create(255.0, 255.0, 255.0);
	if (type == POINT)
	{
		new->light.illumfct = point_illum;
	}
	if (*light_lst == NULL)
	{
		*light_lst = new;
	}
	else
	{
		elem = *light_lst;
		while (elem->next != NULL)
		{
			elem = elem->next;
		}
		elem->next = new;
	}
	return (*light_lst);
}
