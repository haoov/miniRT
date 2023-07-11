#include "object.h"

#include <stdio.h>

t_obj_lst	*sphere_create(void)
{
	t_obj_lst	*sphere;

	sphere = (t_obj_lst *) ft_calloc(1, sizeof (t_obj_lst));
	if (sphere == NULL)
		return (NULL);
	sphere->color = vec_create(1.0, 1.0, 1.0);
	sphere->intfct = sphere_intersect;
	return (sphere);
}

static bool	solve_equation(t_vec v, t_vec ray_origin, double *t1, double *t2)
{
	double	b;
	double	c;
	double	test;

	b = 2.0 * vec_dot(ray_origin, v);
	c = vec_dot(ray_origin, ray_origin) - 1.0;
	test = (b * b) - 4.0 * c;
	if (test > 0.0)
	{
		*t1 = (-b + sqrt(test)) / 2.0;
		*t2 = (-b - sqrt(test)) / 2.0;
		if ((*t1 < 0.0) && (*t2 < 0.0))
			return (false);
		else
			return (true);
	}
	else
		return (false);
}

static bool	compute_intersection(t_ray tfm_ray, t_poi *poi)
{
	t_vec	k;
	double	t1;
	double	t2;

	k = tfm_ray.ab;
	vec_normalize(&k);
	if (!solve_equation(k, tfm_ray.pa, &t1, &t2))
		return (false);
	else
	{
		if (t1 < t2)
		{
			if (t1 > 0.0)
			{
				poi->point = vec_add(tfm_ray.pa, vec_mult(k, t1));
			}
			else
			{
				if (t2 > 0.0)
					poi->point = vec_add(tfm_ray.pa, vec_mult(k, t2));
				else
					return (false);
			}
		}
		else
		{
			if (t2 > 0.0)
			{
				poi->point = vec_add(tfm_ray.pa, vec_mult(k, t2));
			}
			else
			{
				if (t1 > 0.0)
					poi->point = vec_add(tfm_ray.pa, vec_mult(k, t1));
				else
					return (false);
			}
		}
		poi->u = atan2(sqrt(pow(poi->point.x, 2.0)
				+ pow(poi->point.y, 2.0)), poi->point.z);
		poi->v = atan2(poi->point.y, poi->point.x);
		if (poi->point.x < 0)
			poi->v += M_PI;
		poi->u /= M_PI;
		poi->v /= M_PI;
	}
	return (true);
}

bool	sphere_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj)
{
	t_ray	tfm_ray;

	//Apply the rev gtfm to the ray
	tfm_ray = gtfm_ray_apply(cur_obj->gtfm, cam_ray, REV);

	//Compute intersection point
	if (!compute_intersection(tfm_ray, poi))
		return (false);

	//Compute the local normal
	poi->normal = apply_lin_tfm(cur_obj->gtfm, poi->point);
	vec_normalize(&poi->normal);

	//Apply the transform to the point of intersection
	poi->point = gtfm_vec_apply(cur_obj->gtfm, poi->point, FWD);

	poi->color = cur_obj->color;
	poi->obj = cur_obj;
	return (true);
}
