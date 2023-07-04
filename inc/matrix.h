#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include <stdbool.h>

# define X	1
# define Y	2
# define Z	3

typedef struct s_mtx4
{
	double	val[4][4];
}t_mtx4;

typedef struct s_mtx8
{
	double	val[4][8];
}t_mtx8;

void	identity(t_mtx4 *mtx);
t_mtx4	mtx_mult(t_mtx4 mtx1, t_mtx4 mtx2);
bool	invert(t_mtx4 *mtx);
t_vec4	mtx_vec_mult(t_vec4 vec, t_mtx4 m);

void	print_mtx(t_mtx4 mtx);

#endif
