#include "light.h"
#include <math.h>

#include <stdio.h>

bool	point_illum(t_vec *point, t_vec *norm, t_vec *color, double *intensity, t_light light)
{
	t_vec	lightdir; //Vector from the point to the light
	double	angle; //angle between the normal and the light ray

	lightdir = vec_sub(light.pos, *point);
	vec_normalize(&lightdir);

	//Compute the angle between the normal and the light ray
	//We assume that the normal is a unit vector
	angle = acos(vec_dot(*norm, lightdir));

	//If the normal is pointing away from the light we have no illumination
	if (angle > M_PI_2)
	{
		*color = light.color;
		*intensity = 0.0;
		return (false);
	}
	else
	{
		//We have illumination
		*color = light.color;
		*intensity = light.intensity * (1.0 - (angle / M_PI_2));
		return (true);
	}
}
