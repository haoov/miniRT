/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:07:35 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:07:41 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mtx4_row_mult(t_mtx4_8 *mtx, int row, double x)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		mtx->val[row][i] *= x;
		i++;
	}
}

void	mtx4_mult_add(t_mtx4_8 *mtx, int row_mult, double x, int row_add)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		mtx->val[row_add][i] += mtx->val[row_mult][i] * x;
		i++;
	}
}

void	mtx4_swap_rows(t_mtx4_8 *mtx, int row1, int row2)
{
	double	tmp;
	int		i;

	i = 0;
	while (i < 8)
	{
		tmp = mtx->val[row1][i];
		mtx->val[row1][i] = mtx->val[row2][i];
		mtx->val[row2][i] = tmp;
		i++;
	}
}

int	mtx4_max_row(t_mtx4_8 mtx, int ccol, int crow)
{
	double	max;
	int		res;
	int		i;

	i = crow;
	max = mtx.val[crow][ccol];
	res = 0;
	while (i < 4)
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
