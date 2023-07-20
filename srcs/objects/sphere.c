/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:49:54 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:50:55 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_obj	*sphere_create(void)
{
	t_obj	*sphere;

	sphere = (t_obj *) ft_calloc(1, sizeof (t_obj));
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

static double	closest_point(double t1, double t2)
{
	if (t1 < t2)
	{
		if (t1 > 0.0)
			return (t1);
		else
		{
			if (t2 > 0.0)
				return (t2);
			else
				return (0.0);
		}
	}
	else
	{
		if (t2 > 0.0)
			return (t2);
		else
		{
			if (t1 > 0.0)
				return (t1);
			else
				return (0.0);
		}
	}
}

static bool	compute_intersection(t_ray tfm_ray, t_poi *poi)
{
	t_vec	k;
	double	t1;
	double	t2;
	double	t;

	k = tfm_ray.ab;
	vec_normalize(&k);
	if (!solve_equation(k, tfm_ray.pa, &t1, &t2))
		return (false);
	else
	{
		t = closest_point(t1, t2);
		if (t == 0.0)
			return (false);
		poi->point = vec_add(tfm_ray.pa, vec_mult(k, t));
		poi->u = atan2(poi->point.y, poi->point.x) / M_PI;
		poi->v = 2.0 * (atan2(sqrt(pow(poi->point.x, 2.0)
						+ pow(poi->point.y, 2.0)), poi->point.z) / M_PI) - 1.0;
	}
	return (true);
}

bool	sphere_intersect(t_ray cam_ray, t_poi *poi, t_obj *cur_obj)
{
	t_ray	tfm_ray;
	t_vec	origin;
	t_vec	new_origin;

	tfm_ray = gtfm_ray_apply(cur_obj->gtfm, cam_ray, REV);
	if (!compute_intersection(tfm_ray, poi))
		return (false);
	poi->point = gtfm_vec_apply(cur_obj->gtfm, poi->point, FWD);
	origin = vec_create(0.0, 0.0, 0.0);
	new_origin = gtfm_vec_apply(cur_obj->gtfm, origin, FWD);
	poi->normal = vec_sub(poi->point, new_origin);
	vec_normalize(&poi->normal);
	poi->color = cur_obj->color;
	poi->obj = cur_obj;
	return (true);
}
