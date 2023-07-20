/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:57:57 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:57:58 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_create(t_vec start, t_vec point)
{
	t_ray	ray;

	ray.pa = start;
	ray.pb = point;
	ray.ab = vec_sub(point, start);
	return (ray);
}
