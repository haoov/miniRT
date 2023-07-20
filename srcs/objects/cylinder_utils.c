/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:48:50 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:48:51 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <math.h>

bool	solve_equation(t_ray tfm_ray, t_vec v, double t[4])
{
	double	a;
	double	b;
	double	c;
	double	numsqrt;

	a = pow(v.x, 2.0) + pow(v.y, 2.0);
	b = 2.0 * (tfm_ray.pa.x * v.x + tfm_ray.pa.y * v.y);
	c = pow(tfm_ray.pa.x, 2.0) + pow(tfm_ray.pa.y, 2.0) - 1.0;
	numsqrt = sqrt(pow(b, 2.0) - 4 * a * c);
	if (numsqrt <= 0.0 && close_enough(v.z, 0.0))
		return (false);
	if (numsqrt > 0.0)
	{
		t[0] = (-b + numsqrt) / (2 * a);
		t[1] = (-b - numsqrt) / (2 * a);
	}
	if (!close_enough(v.z, 0.0))
	{
		t[2] = (tfm_ray.pa.z - 1.0) / -v.z;
		t[3] = (tfm_ray.pa.z + 1.0) / -v.z;
	}
	return (true);
}

bool	check_valid_int(t_ray tfm_ray, t_vec v, double t[4], t_vec intp[4])
{
	intp[0] = vec_add(tfm_ray.pa, vec_mult(v, t[0]));
	intp[1] = vec_add(tfm_ray.pa, vec_mult(v, t[1]));
	intp[2] = vec_add(tfm_ray.pa, vec_mult(v, t[2]));
	intp[3] = vec_add(tfm_ray.pa, vec_mult(v, t[3]));
	if (!(t[0] > 0.0 && fabs(intp[0].z) < 1.0))
		t[0] = 100e6;
	if (!(t[1] > 0.0 && fabs(intp[1].z) < 1.0))
		t[1] = 100e6;
	if (!(t[2] > 0.0 && sqrt(pow(intp[2].x, 2.0) + pow(intp[2].y, 2.0)) < 1.0))
		t[2] = 100e6;
	if (!(t[3] > 0.0 && sqrt(pow(intp[3].x, 2.0) + pow(intp[3].y, 2.0)) < 1.0))
		t[3] = 100e6;
	if (t[0] == 100e6 && t[1] == 100e6 && t[2] == 100e6 && t[3] == 100e6)
		return (false);
	return (true);
}

int	closest_point(const double t[4])
{
	int		min_index;
	int		index;
	double	min_val;

	index = 0;
	min_val = 10e6;
	while (index < 4)
	{
		if (t[index] < min_val)
		{
			min_val = t[index];
			min_index = index;
		}
		++index;
	}
	return (min_index);
}
