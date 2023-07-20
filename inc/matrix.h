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

t_mtx4		mtx4_identity(t_mtx4 *mtx);
t_mtx4		mtx4_mult(t_mtx4 mtx1, t_mtx4 mtx2);
bool		mtx4_invert(t_mtx4 *mtx);
t_vec4		mtx4_vec_mult(t_vec4 vec, t_mtx4 m);
t_mtx4_8	mtx4_join_mtx(t_mtx4 mtx1, t_mtx4 mtx2);
void		mtx4_sep_mtx(t_mtx4_8 mtx, t_mtx4 *mtx1, t_mtx4 *mtx2);
bool		mtx4_is_identity(t_mtx4 mtx);
void		mtx4_row_mult(t_mtx4_8 *mtx, int row, double x);
void		mtx4_mult_add(t_mtx4_8 *mtx, int row_mult, double x, int row_add);
void		mtx4_swap_rows(t_mtx4_8 *mtx, int row1, int row2);
int			mtx4_max_row(t_mtx4_8 mtx, int ccol, int crow);
t_mtx4_8	mtx4_join_identity(t_mtx4 mtx);

bool		mtx3_invert(t_mtx3 *mtx);
t_mtx3		mtx3_mult(t_mtx3 mtx1, t_mtx3 mtx2);
void		mtx3_identity(t_mtx3 *mtx);
t_vec		mtx3_vec_mult(t_vec vec, t_mtx3 m);
t_mtx3		mtx3_transpose(t_mtx3 mtx);
t_mtx3		mtx3_extract_linear(t_mtx4 mtx);
t_mtx3_6 	mtx3_join_mtx(t_mtx3 mtx1, t_mtx3 mtx2);
void		mtx3_sep_mtx(t_mtx3_6 mtx, t_mtx3 *mtx1, t_mtx3 *mtx2);
void		mtx3_row_mult(t_mtx3_6 *mtx, int row, double x);
void		mtx3_mult_add(t_mtx3_6 *mtx, int row_mult, double x, int row_add);
void		mtx3_swap_rows(t_mtx3_6 *mtx, int row1, int row2);
int			mtx3_max_row(t_mtx3_6 mtx, int ccol, int crow);
bool		mtx3_is_identity(t_mtx3 mtx);
t_mtx3_6 	mtx3_join_identity(t_mtx3 mtx);

bool		close_enough(double val1, double val2);

#endif
