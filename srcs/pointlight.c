#include "light.h"
#include <math.h>

#include <stdio.h>

bool	point_illum(t_vec *point, t_vec *norm, t_vec *color, double *intensity,
					t_light light, t_obj_lst *obj_lst, t_obj_lst *cur_obj)
{
	t_vec	lightdir; //Vector from the point to the light
	double	angle; //angle between the normal and the light ray

	lightdir = vec_sub(light.pos, *point);
	vec_normalize(&lightdir);

	//Compute a starting point
	t_vec	start_point;
	start_point = *point;

	//Construct a ray from the point of intersection to the light
	t_ray	light_ray;
	light_ray = ray_create(start_point, light.pos);

	//check for intersection with all of the object exept the current one
	t_vec	poi;
	t_vec	poi_normal;
	t_vec	poi_color;
	bool	valid_int = false;

	while (obj_lst != NULL)
	{
		if (obj_lst != cur_obj)
		{
			valid_int = obj_lst->obj.intfct(light_ray, &poi, &poi_normal,
											&poi_color, obj_lst->obj);
		}

		/*If we have an intersection we dont need to check further because this
		object is blocking the light*/
		if (valid_int)
		{
			break;
		}
		obj_lst = obj_lst->next;
	}

	/*Only continue if the light ray didnt intersect with anything*/
	if (!valid_int)
	{
		//Compute the angle between the normal amd the lightray
		angle = acos(vec_dot(*norm, lightdir));

		//If the normal is pointing away from the light then no illumination
		if (angle > M_PI_2)
		{
			//No illum
			*color = light.color;
			*intensity = 0.0;
			return (false);
		}
		else
		{
			//Illum
			*color = light.color;
			*intensity = light.intensity * (1.0 - (angle / M_PI_2));
			return (true);
		}
	}
	else
	{
		//Shadow
		*color = light.color;
		*intensity = 0.0;
		return (false);
	}
}
