#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include <stdbool.h>

# define X	1
# define Y	2
# define Z	3

typedef	struct s_mtx3
{
	double	val[3][3];
}t_mtx3;

typedef struct s_mtx4
{
	double	val[4][4];
}t_mtx4;

typedef struct s_mtx3_6
{
	double	val[3][6];
}t_mtx3_6;

typedef struct s_mtx4_8
{
	double	val[4][8];
}t_mtx4_8;

void	mtx4_identity(t_mtx4 *mtx);
t_mtx4	mtx4_mult(t_mtx4 mtx1, t_mtx4 mtx2);
bool	mtx4_invert(t_mtx4 *mtx);
t_vec4	mtx_vec_mult(t_vec4 vec, t_mtx4 m);

bool	mtx3_invert(t_mtx3 *mtx);
t_mtx3	mtx3_mult(t_mtx3 mtx1, t_mtx3 mtx2);
void	mtx_3identity(t_mtx3 *mtx);
t_vec	mtx3_vec_mult(t_vec vec, t_mtx3 m);

bool	close_enough(double val1, double val2);

void	print_mtx4(t_mtx4 mtx);

#endif
