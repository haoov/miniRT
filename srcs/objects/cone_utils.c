/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:50:38 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:50:46 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <math.h>

bool	cn_solve_equation(t_ray tfm_r, t_vec v, double t[3])
{
	double	a;
	double	b;
	double	c;
	double	numsqrt;

	a = pow(v.x, 2.0) + pow(v.y, 2.0) - pow(v.z, 2.0);
	b = 2.0 * (tfm_r.pa.x * v.x + tfm_r.pa.y * v.y - tfm_r.pa.z * v.z);
	c = pow(tfm_r.pa.x, 2.0) + pow(tfm_r.pa.y, 2.0) - pow(tfm_r.pa.z, 2.0);
	numsqrt = sqrt(pow(b, 2.0) - 4 * a * c);
	if (numsqrt <= 0.0 && close_enough(v.z, 0.0))
		return (false);
	if (numsqrt > 0.0)
	{
		t[0] = (-b + numsqrt) / (2 * a);
		t[1] = (-b - numsqrt) / (2 * a);
	}
	if (!close_enough(v.z, 0.0))
		t[2] = (tfm_r.pa.z - 1.0) / -v.z;
	return (true);
}

bool	cn_check_valid_int(t_ray tfm_ray, t_vec v, double t[3], t_vec intp[3])
{
	intp[0] = vec_add(tfm_ray.pa, vec_mult(v, t[0]));
	intp[1] = vec_add(tfm_ray.pa, vec_mult(v, t[1]));
	intp[2] = vec_add(tfm_ray.pa, vec_mult(v, t[2]));
	if (!(t[0] > 0.0 && intp[0].z > 0.0 && intp[0].z < 1.0))
		t[0] = 100e6;
	if (!(t[1] > 0.0 && intp[1].z > 0.0 && intp[1].z < 1.0))
		t[1] = 100e6;
	if (!(t[2] > 0.0 && sqrt(pow(intp[2].x, 2.0) + pow(intp[2].y, 2.0)) < 1.0))
		t[2] = 100e6;
	if (t[0] == 100e6 && t[1] == 100e6 && t[2] == 100e6)
		return (false);
	return (true);
}

int	cn_closest_point(const double t[3])
{
	int		min_index;
	int		index;
	double	min_val;

	index = 0;
	min_val = 10e6;
	while (index < 3)
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
