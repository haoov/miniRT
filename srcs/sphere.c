#include "object.h"

bool	sphere_intersect(t_ray ray, t_vec p, t_vec *norm, t_vec *color)
{
	t_vec	v;
	double	b;
	double	c;
	double	test;

	(void)p;
	(void)norm;
	(void)color;

	/*Note that a is equal to the squared norm of the direction of the
	 * cast ray> As this will be a unit vector we can conclude that
	 * the value of a will always be 1*/
	//a = 1;

	v = ray.ab;
	vec_normalize(&v);
	b = 2.0 * vec_dot(ray.pa, v);
	c = vec_dot(ray.pa, ray.pa) - 1.0;
	test = (b * b) - 4.0 * c;
	if (test > 0.0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
