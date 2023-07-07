#include "object.h"
#include <math.h>

t_obj_lst	*plane_create(void)
{
	t_obj_lst	*plane;

	plane = (t_obj_lst *) ft_calloc(1, sizeof (t_obj_lst));
	if (plane == NULL)
		return (NULL);
	plane->color = vec_create(0.0, 0.0, 0.0);
	plane->intfct = plane_intersect;
	return (plane);
}

static bool	solve_equation(t_vec k, t_vec ray_origin, double *t, t_poi *poi)
{
	double	u;
	double	v;

	if (!close_enough(k.z, 0.0))
	{
		*t = ray_origin.z / -k.z;
		if (*t > 0.0)
		{
			u = ray_origin.x + k.x * (*t);
			v = ray_origin.y + k.y * (*t);
			if (fabs(u) < 1.0 && fabs(v) < 1.0)
			{
				poi->u = u;
				poi->v = v;
				return (true);
			}
			else
				return (false);
		}
		else
			return (false);
	}
	else
		return (false);
}

static bool	compute_intersection(t_ray tfm_ray, t_poi *poi)
{
	t_vec	k;
	double	t;

	k = tfm_ray.ab;
	vec_normalize(&k);
	if (!solve_equation(k, tfm_ray.pa, &t, poi))
		return (false);
	poi->point = vec_add(tfm_ray.pa, vec_mult(k, t));
	return (true);
}

bool	plane_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj)
{
	t_ray	tfm_ray;
	t_vec	origin;
	t_vec	new_origin;
	t_vec	normal_vec;

	tfm_ray = gtfm_ray_apply(cur_obj->gtfm, cam_ray, REV);

	//Compute intersection point
	if (!compute_intersection(tfm_ray, poi))
		return (false);

	//Transform the poi back to the world coordinates
	poi->point = gtfm_vec_apply(cur_obj->gtfm, poi->point, FWD);

	//Compute the normal
	normal_vec = vec_create(0.0, 0.0, -1.0);
	origin = vec_create(0.0, 0.0, 0.0);
	new_origin = gtfm_vec_apply(cur_obj->gtfm, origin, FWD);
	poi->normal = vec_sub(gtfm_vec_apply(cur_obj->gtfm, normal_vec, FWD),
						  new_origin);
	vec_normalize(&poi->normal);

	//Return the base color
	poi->color = cur_obj->color;
	poi->obj = cur_obj;
	return (true);
}

/*bool	plane_intersect(t_ray ray, t_vec *p, t_vec *norm, t_vec *color, t_obj obj)
{
	t_ray	tfm_ray;
	tfm_ray = gtfm_ray_apply(obj.gtfm, ray, REV);

	t_vec	k;
	k = tfm_ray.ab;
	vec_normalize(&k);

	//check if there is an intersection so if the ray is not parallel to the plane
	if (!close_enough(k.z, 0.0))
	{
		//there is an intersection
		double	t;
		t = tfm_ray.pa.z / -k.z;

		//if t is < 0 the the intersection is behind the camera so we ignore it
		if (t > 0.0)
		{
			//Compute the values for u and v
			double u;
			double v;
			u = tfm_ray.pa.x + k.x * t;
			v = tfm_ray.pa.y + k.y * t;

			//If the magnitude of u and v is less than or equal to 1 then we must be in the plane
			if (fabs(u) < 1.0 && fabs(v) < 1.0)
			{
				//Compute the point of intersection
				t_vec	poi;
				poi = vec_add(tfm_ray.pa, vec_mult(k, t));

				//Transform the poi back to the world coordinates
				*p = gtfm_vec_apply(obj.gtfm, poi, FWD);

				//Compute the norm
				t_vec	origin;
				t_vec	new_origin;
				t_vec	normal_vec;
				normal_vec = vec_create(0.0, 0.0, -1.0);
				origin = vec_create(0.0, 0.0, 0.0);
				new_origin = gtfm_vec_apply(obj.gtfm, origin, FWD);
				*norm = vec_sub(gtfm_vec_apply(obj.gtfm, normal_vec, FWD), new_origin);
				vec_normalize(norm);

				//Return the base color
				*color = obj.color;

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
	return (false);
}*/
