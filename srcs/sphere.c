#include "object.h"

#include <stdio.h>

bool	sphere_intersect(t_ray ray, t_vec *p, t_vec *norm, t_vec *color, t_obj obj)
{
	t_vec	v;
	t_vec	poi;
	double	b;
	double	c;
	double	test;
    double  sqrtnum;
    double  t1;
    double  t2;

	//Apply the rev gtfm to the ray
	t_ray	tfm_ray;
	tfm_ray = gtfm_ray_apply(obj.gtfm, ray, REV);

	v = tfm_ray.ab;
	vec_normalize(&v);
    b = 2.0 * vec_dot(tfm_ray.pa, v);
	c = vec_dot(tfm_ray.pa, tfm_ray.pa) - 1.0;
	test = (b * b) - 4.0 * c;
	if (test > 0.0)
	{
        sqrtnum = sqrt(test);
        t1 = (-b + sqrtnum) / 2.0;
        t2 = (-b - sqrtnum) / 2.0;
        if (t1 < 0.0 || t2 < 0.0)
        {
            return (false);
        }
        else
        {
            if (t1 < t2)
            {
                poi = vec_add(tfm_ray.pa, vec_mult(v, t1));
            }
            else
            {
                poi = vec_add(tfm_ray.pa, vec_mult(v, t2));
            }

			//Apply the transform to the point of intersection
			*p = gtfm_vec_apply(obj.gtfm, poi, FWD);

			//Compute the local normal
			t_vec	obj_origin;
			t_vec 	obj_new_origin;
			obj_origin = vec_create(0.0, 0.0, 0.0);
			obj_new_origin = gtfm_vec_apply(obj.gtfm, obj_origin, FWD);
			*norm = vec_sub(*p, obj_new_origin);
			vec_normalize(norm);

			*color = obj.color;
        }
		return (true);
	}
	else
	{
		return (false);
	}
}
