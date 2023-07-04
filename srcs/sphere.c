#include "object.h"

bool	sphere_intersect(t_ray ray, t_vec *p, t_vec *norm, t_vec *color)
{
	t_vec	v;
	double	b;
	double	c;
	double	test;
    double  sqrtnum;
    double  t1;
    double  t2;

	(void)norm;
	(void)color;
	v = ray.ab;
	vec_normalize(&v);
    b = 2.0 * vec_dot(ray.pa, v);
	c = vec_dot(ray.pa, ray.pa) - 1.0;
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
                *p = vec_add(ray.pa, vec_mult(v, t1));
            }
            else
            {
                *p = vec_add(ray.pa, vec_mult(v, t2));
            }

			//Compute the local normal
			*norm = *p;
			vec_normalize(norm);
        }
		return (true);
	}
	else
	{
		return (false);
	}
}
