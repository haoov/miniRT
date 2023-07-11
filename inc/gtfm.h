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
	t_mtx3	lin_tfm_mtx;
}t_gtfm;

void	init_gtfm(t_gtfm *gtfm);
t_ray	gtfm_ray_apply(t_gtfm gtfm,t_ray ray, int tfm);
t_vec	gtfm_vec_apply(t_gtfm gtfm, t_vec vec, int tfm);
t_vec	apply_lin_tfm(t_gtfm gtfm, t_vec vec);
t_gtfm	gtfm_set(t_vec trans, t_vec rot, t_vec scale);

#endif
