/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:05:44 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:05:49 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mtx3_row_mult(t_mtx3_6 *mtx, int row, double x)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		mtx->val[row][i] *= x;
		i++;
	}
}

void	mtx3_mult_add(t_mtx3_6 *mtx, int row_mult, double x, int row_add)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		mtx->val[row_add][i] += mtx->val[row_mult][i] * x;
		i++;
	}
}

void	mtx3_swap_rows(t_mtx3_6 *mtx, int row1, int row2)
{
	double	tmp;
	int		i;

	i = 0;
	while (i < 6)
	{
		tmp = mtx->val[row1][i];
		mtx->val[row1][i] = mtx->val[row2][i];
		mtx->val[row2][i] = tmp;
		i++;
	}
}

int	mtx3_max_row(t_mtx3_6 mtx, int ccol, int crow)
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

bool	mtx3_is_identity(t_mtx3 mtx)
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
					return (false);
			}
			else
			{
				if (!close_enough(mtx.val[row][col], 0.0))
					return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}
