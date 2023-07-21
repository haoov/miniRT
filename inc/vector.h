/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:36:53 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:36:54 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}t_vec;

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}t_vec4;

t_vec	vec_create(double x, double y, double z);
t_vec4	vec4_create(double x, double y, double z, double w);
t_vec	vec_sub(t_vec vec1, t_vec vec2);
t_vec	vec_add(t_vec vec1, t_vec vec2);
t_vec	vec_mult(t_vec vec, double scalar);
t_vec	vec_cross(t_vec vec1, t_vec vec2);
double	vec_norm(t_vec vec);
double	vec_dot(t_vec vec1, t_vec vec2);
void	vec_normalize(t_vec *vec);
t_vec	vec_normalized(t_vec vec);

void	vec_print(t_vec vec);

#endif //VECTOR_H
