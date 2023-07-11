#include "object.h"
#include <math.h>

t_obj_lst	*cylinder_create(void)
{
	t_obj_lst	*cylinder;

	cylinder = (t_obj_lst *) ft_calloc(1, sizeof (t_obj_lst));
	if (cylinder == NULL)
		return (NULL);
	cylinder->color = vec_create(1.0, 1.0, 1.0);
	cylinder->intfct = cylinder_intersect;
	return (cylinder);
}

bool	cylinder_intersect(t_ray cast_ray, t_poi *poi, t_obj_lst *obj_cur)
{
	t_ray 	tfm_ray;

	//Apply rev transform to the ray
	tfm_ray = gtfm_ray_apply(obj_cur->gtfm, cast_ray, REV);

	//ab vector from ray and normalize
	t_vec	v;
	v = tfm_ray.ab;
	vec_normalize(&v);

	//Starting point
	t_vec	p;
	p = tfm_ray.pa;

	//Compute a b and c
	double	a;
	double	b;
	double	c;
	a = pow(v.x, 2.0) + pow(v.y, 2.0);
	b = 2.0 * (p.x * v.x + p.y * v.y);
	c = pow(p.x, 2.0) + pow(p.y, 2.0) - 1.0;

	//Compute b^2 +- 4ac
	double	numsqrt;
	numsqrt = sqrt(pow(b, 2.0) - 4 * a * c);

	//Test for intersections
	//First with the cylinder itself
	t_vec	intp[4];
	double	t[4];
	bool	t_valid[4];

	if (numsqrt > 0.0)
	{
		//There was an intersection
		//Computes values for t
		t[0] = (-b + numsqrt) / (2 * a);
		t[1] = (-b - numsqrt) / (2 * a);

		//Compute the point of intersection
		intp[0] = vec_add(tfm_ray.pa, vec_mult(v, t[0]));
		intp[1] = vec_add(tfm_ray.pa, vec_mult(v, t[1]));

		//Check if any is valid
		if (t[0] > 0.0 && fabs(intp[0].z) < 1.0)
		{
			t_valid[0] = true;
		}
		else
		{
			t_valid[0] = false;
			t[0] = 100e6;
		}
		if (t[1] > 0.0 && fabs(intp[1].z) < 1.0)
		{
			t_valid[1] = true;
		}
		else
		{
			t_valid[1] = false;
			t[1] = 100e6;
		}
	}
	else
	{
		t_valid[0] = false;
		t_valid[1] = false;
		t[0] = 100e6;
		t[1] = 100e6;
	}

	//And test the end caps
	if (close_enough(v.z, 0.0))
	{
		t_valid[2] = false;
		t_valid[3] = false;
		t[2] = 100e6;
		t[3] = 100e6;
	}
	else
	{
		t[2] = (tfm_ray.pa.z - 1.0) / -v.z;
		t[3] = (tfm_ray.pa.z + 1.0) / -v.z;

		//Compute the intersection
		intp[2] = vec_add(tfm_ray.pa, vec_mult(v, t[2]));
		intp[3] = vec_add(tfm_ray.pa, vec_mult(v, t[3]));

		//Check if theses are valid
		if (t[2] > 0.0 && sqrt(pow(intp[2].x, 2.0) + pow(intp[2].y, 2.0)) < 1.0)
		{
			t_valid[2] = true;
		}
		else
		{
			t_valid[2] = false;
			t[2] = 100e6;
		}
		if (t[3] > 0.0 && sqrt(pow(intp[3].x, 2.0) + pow(intp[3].y, 2.0)) < 1.0)
		{
			t_valid[3] = true;
		}
		else
		{
			t_valid[3] = false;
			t[3] = 100e6;
		}
	}

	//If no valid int then we stop
	if (!t_valid[0] && !t_valid[1] && !t_valid[2] && !t_valid[3])
		return (false);

	//Check for the smallest value of t
	int		min_index;
	double	min_value = 10e6;
	int		index = 0;
	while (index < 4)
	{
		if (t[index] < min_value)
		{
			min_value = t[index];
			min_index = index;
		}
		++index;
	}

	//If min index is 0 or 1 then intersect with the cylinder
	t_vec	valid_intp;
	valid_intp = intp[min_index];
	if (min_index < 2)
	{
		//Transform the int point back to the world coordinates
		poi->point = gtfm_vec_apply(obj_cur->gtfm, valid_intp, FWD);

		//Compute the local normal
		t_vec	org_normal;
		t_vec	new_normal;
		t_vec	origin;
		t_vec	new_origin;
		origin = vec_create(0.0, 0.0, 0.0);
		new_origin = gtfm_vec_apply(obj_cur->gtfm, origin, FWD);
		org_normal.x = valid_intp.x;
		org_normal.y = valid_intp.y;
		org_normal.z = 0.0;
		new_normal = vec_sub(gtfm_vec_apply(obj_cur->gtfm, org_normal, FWD),
							 new_origin);
		vec_normalize(&new_normal);
		poi->normal = new_normal;
		poi->color = obj_cur->color;
		poi->obj = obj_cur;

		//Compute u and v
		poi->u = atan2(valid_intp.y, valid_intp.x) / M_PI;
		poi->v = valid_intp.z;

		return (true);
	}
	else
	{
		//Then check the end caps
		if (!close_enough(v.z, 0.0))
		{
			//Check if inside the disk
			if (sqrt(pow(valid_intp.x, 2.0) + pow(valid_intp.y, 2.0)) < 1.0)
			{
				//Transform back into world coordinate
				poi->point = gtfm_vec_apply(obj_cur->gtfm, valid_intp, FWD);

				//Compute the local normal
				t_vec	origin;
				t_vec	new_origin;
				t_vec	normal_vec;
				normal_vec = vec_create(0.0, 0.0, 0.0 + valid_intp.z);
				origin = vec_create(0.0, 0.0, 0.0);
				new_origin = gtfm_vec_apply(obj_cur->gtfm, origin, FWD);
				poi->normal = vec_sub(gtfm_vec_apply(obj_cur->gtfm,
													 normal_vec, FWD), new_origin);
				vec_normalize(&poi->normal);
				poi->color = obj_cur->color;
				poi->obj = obj_cur;

				//Compute u and v
				poi->u = valid_intp.x;
				poi->v = valid_intp.y;

				return (true);
			}
			else
			{
				return (false);
			}
		}
		else
		{
			return (false);
		}
	}
}



























