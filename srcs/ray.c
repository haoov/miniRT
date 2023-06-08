#include "ray.h"

t_ray	ray_create(t_vec start, t_vec point)
{
	t_ray	ray;

	ray.pa = start;
	ray.pb = point;
	ray.ab = vec_sub(point, start);
	return (ray);
}
