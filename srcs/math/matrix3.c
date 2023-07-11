#include "matrix.h"
#include "libft.h"
#include <math.h>

//DEBUG
#include <stdio.h>
void	print_mtx3(t_mtx3 mtx)
{
	printf("%f %f %f\n", mtx.val[0][0], mtx.val[0][1], mtx.val[0][2]);
	printf("%f %f %f\n", mtx.val[1][0], mtx.val[1][1], mtx.val[1][2]);
	printf("%f %f %f\n", mtx.val[2][0], mtx.val[2][1], mtx.val[2][2]);
	printf("\n");
}

t_mtx3	mtx3_add(t_mtx3 mtx1, t_mtx3 mtx2)
{
	t_mtx3	res;
	int		l;
	int		c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 3)
		{
			res.val[l][c] = mtx1.val[l][c] + mtx2.val[l][c];
			c++;
		}
		l++;
	}
	return (res);
}

t_mtx3	mtx3_sub(t_mtx3 mtx1, t_mtx3 mtx2)
{
	t_mtx3	res;
	int		l;
	int		c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 3)
		{
			res.val[l][c] = mtx1.val[l][c] - mtx2.val[l][c];
			c++;
		}
		l++;
	}
	return (res);
	return (res);
}

t_mtx3	mtx3_mult(t_mtx3 mtx1, t_mtx3 mtx2)
{
	t_mtx3	res;
	int		l;
	int		c;
	int		i;

	ft_memset(&res, 0, sizeof (t_mtx4));
	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 3)
		{
			i = 0;
			while (i < 3)
			{
				res.val[l][c] += mtx1.val[l][i] * mtx2.val[i][c];
				i++;
			}
			c++;
		}
		l++;
	}
	return (res);
}

t_vec	mtx3_vec_mult(t_vec vec, t_mtx3 m)
{
	t_vec	res;

	res.x = vec.x * m.val[0][0] + vec.y * m.val[0][1] + vec.z * m.val[0][2];
	res.y = vec.x * m.val[1][0] + vec.y * m.val[1][1] + vec.z * m.val[1][2];
	res.z = vec.x * m.val[2][0] + vec.y	* m.val[2][1] + vec.z * m.val[2][2];
	return (res);
}

t_mtx3	mtx3_transpose(t_mtx3 mtx)
{
	t_mtx3	res;
	int		l;
	int		c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 3)
		{
			res.val[l][c] = mtx.val[c][l];
			c++;
		}
		l++;
	}
	return (res);
}

t_mtx3	mtx3_extract_linear(t_mtx4 mtx)
{
	t_mtx3	res;
	int		l;
	int		c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 3)
		{
			res.val[l][c] = mtx.val[c][l];
			c++;
		}
		l++;
	}
	return (res);
}

void	mtx3_identity(t_mtx3 *mtx)
{
	int l;
	int c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 3)
		{
			if (l == c)
			{
				mtx->val[l][c] = 1;
			}
			else
			{
				mtx->val[l][c] = 0;
			}
			c++;
		}
		l++;
	}
}

//Inverse
static t_mtx3_6 	join_mtx(t_mtx3 mtx1, t_mtx3 mtx2)
{
	t_mtx3_6 	res;
	int	l;
	int c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 6)
		{
			while (c < 3)
			{
				res.val[l][c] = mtx1.val[l][c];
				c++;
			}
			res.val[l][c] = mtx2.val[l][c - 3];
			c++;
		}
		l++;
	}
	return (res);
}

static void	sep_mtx(t_mtx3_6 mtx, t_mtx3 *mtx1, t_mtx3 *mtx2)
{
	int	l;
	int c;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 6)
		{
			while (c < 3)
			{
				mtx1->val[l][c] = mtx.val[l][c];
				c++;
			}
			mtx2->val[l][c - 3] = mtx.val[l][c];
			c++;
		}
		l++;
	}
}

static void	row_mult(t_mtx3_6 *mtx, int row, double x)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		mtx->val[row][i] *= x;
		i++;
	}
}

static void	row_mult_add(t_mtx3_6 *mtx, int row_mult, double x, int row_add)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		mtx->val[row_add][i] += mtx->val[row_mult][i] * x;
		i++;
	}
}

static void	swap_rows(t_mtx3_6 *mtx, int row1, int row2)
{
	double	tmp;
	int 	i;

	i = 0;
	while (i < 6)
	{
		tmp = mtx->val[row1][i];
		mtx->val[row1][i] = mtx->val[row2][i];
		mtx->val[row2][i] = tmp;
		i++;
	}
}

static int	max_row(t_mtx3_6 mtx, int ccol, int crow)
{
	double	max;
	int		res;
	int		i;

	i = crow;
	max = mtx.val[crow][ccol];
	res = 0;
	while (i < 3)
	{
		if (mtx.val[i][ccol] >= max)
		{
			max = mtx.val[i][ccol];
			res = i;
		}
		i++;
	}
	return (res);
}

static bool	is_identity(t_mtx3 mtx)
{
	int	row;
	int	col;

	row = 0;
	while (row < 3)
	{
		col = 0;
		while (col < 3)
		{
			if (row == col)
			{
				if (!close_enough(mtx.val[row][col], 1.0))
				{
					return (false);
				}
			}
			else
			{
				if (!close_enough(mtx.val[row][col], 0.0))
				{
					return (false);
				}
			}
			col++;
		}
		row++;
	}
	return (true);
}

bool	mtx3_invert(t_mtx3 *mtx)
{
	t_mtx3		id_mtx;
	t_mtx3_6	tmp_mtx;
	t_mtx3		left;
	t_mtx3 		right;

	mtx3_identity(&id_mtx);
	tmp_mtx = join_mtx(*mtx, id_mtx);

	int		crow;
	int		ccol;
	int		row_index;
	int		row1_index;
	double	celem_val;
	double	felem_val;
	int		col_index;
	int		diag_index = 0;
	int		max_index;
	int 	max_count = 100;
	int		count = 0;
	double	mult_fact;
	double	correc_fact;
	bool	complete = false;
	double	div;

	while (complete == false && count < max_count)
	{
		while (diag_index < 3)
		{
			crow = diag_index;
			ccol = diag_index;

			max_index = max_row(tmp_mtx, ccol, crow);
			if (max_index != crow)
			{
				swap_rows(&tmp_mtx, crow, max_index);
			}

			if (tmp_mtx.val[crow][ccol] != 1)
			{
				div = tmp_mtx.val[crow][ccol];
				if (div == 0.0)
					div = 1.0;
				mult_fact = 1.0 / div;
				//printf("Mult row %d by %f\n", crow, mult_fact);
				row_mult(&tmp_mtx, crow, mult_fact);
			}

			row_index = crow + 1;
			while (row_index < 3)
			{
				if (!close_enough(tmp_mtx.val[row_index][ccol], 0.0))
				{
					row1_index = ccol;

					celem_val = tmp_mtx.val[row_index][ccol];
					felem_val = tmp_mtx.val[row1_index][ccol];
					if (felem_val == 0.0)
						felem_val = 1.0;

					if (!close_enough(felem_val, 0.0))
					{
						correc_fact = -(celem_val / felem_val);
						//printf("col : Mult row %d by %f and add it to row %d\n", row1_index, correc_fact, row_index);
						row_mult_add(&tmp_mtx, row1_index, correc_fact, row_index);
					}
				}
				row_index++;
			}

			col_index = ccol + 1;
			while (col_index < 3)
			{
				if (!close_enough(tmp_mtx.val[crow][col_index], 0.0))
				{
					row1_index = col_index;

					celem_val = tmp_mtx.val[crow][col_index];
					felem_val = tmp_mtx.val[row1_index][col_index];
					if (felem_val == 0.0)
						felem_val = 1.0;

					if (!close_enough(felem_val, 0.0))
					{
						correc_fact = -(celem_val / felem_val);
						//printf("row : Mult row %d by %f and add it to row %d\n", row1_index, correc_fact, crow);
						row_mult_add(&tmp_mtx, row1_index, correc_fact, crow);
					}
				}
				col_index++;
			}
			diag_index++;
		}
		sep_mtx(tmp_mtx, &left, &right);
		if (is_identity(left))
		{
			complete = true;
			*mtx = right;
		}
		diag_index = 0;
		count++;
	}
	return (complete);
}
