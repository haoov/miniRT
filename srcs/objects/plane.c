/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:08:15 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 16:08:40 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <math.h>

t_obj	*plane_create(void)
{
	t_obj	*plane;

	plane = (t_obj *) ft_calloc(1, sizeof (t_obj));
	if (plane == NULL)
		return (NULL);
	plane->color = vec_create(1.0, 1.0, 1.0);
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

bool	plane_intersect(t_ray cam_ray, t_poi *poi, t_obj *cur_obj)
{
	t_ray	tfm_ray;
	t_vec	normal_vec;
	t_vec	origin;
	t_vec	new_origin;

	tfm_ray = gtfm_ray_apply(cur_obj->gtfm, cam_ray, REV);
	if (!compute_intersection(tfm_ray, poi))
		return (false);
	poi->point = gtfm_vec_apply(cur_obj->gtfm, poi->point, FWD);
	origin = vec_create(0.0, 0.0, 0.0);
	normal_vec = vec_create(0.0, 0.0, -1.0);
	new_origin = gtfm_vec_apply(cur_obj->gtfm, origin, FWD);
	poi->normal = vec_sub(gtfm_vec_apply(cur_obj->gtfm, normal_vec, FWD),
			new_origin);
	vec_normalize(&poi->normal);
	poi->color = cur_obj->color;
	poi->obj = cur_obj;
	return (true);
}
