/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:19:08 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:19:20 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFM_H
# define GTFM_H

# include "vector.h"
# include "matrix.h"
# include "ray.h"

# define FWD	0
# define REV	1

typedef struct s_gtfm
{
	t_mtx4	tfm_mtx;
	t_mtx4	revtfm_mtx;
}t_gtfm;

t_ray	gtfm_ray_apply(t_gtfm gtfm, t_ray ray, int tfm);
t_vec	gtfm_vec_apply(t_gtfm gtfm, t_vec vec, int tfm);
t_gtfm	gtfm_set(t_vec trans, t_vec rot, t_vec scale);
t_mtx4	trans_mtx(t_vec trans);
t_mtx4	scale_mtx(t_vec scale);
t_mtx4	rotx_mtx(t_vec rot);
t_mtx4	roty_mtx(t_vec rot);
t_mtx4	rotz_mtx(t_vec rot);

#endif
