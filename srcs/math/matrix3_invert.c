/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3_invert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:04:26 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:08:16 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static void	check_max(t_mtx3_6 *mtx, int crow, int ccol)
{
	int		max_index;
	double	div;
	double	mult_fact;

	max_index = mtx3_max_row(*mtx, ccol, crow);
	if (max_index != crow)
	{
		mtx3_swap_rows(mtx, crow, max_index);
	}
	if (mtx->val[crow][ccol] != 1)
	{
		div = mtx->val[crow][ccol];
		if (div == 0.0)
			div = 1.0;
		mult_fact = 1.0 / div;
		mtx3_row_mult(mtx, crow, mult_fact);
	}
}

static void	row_op(t_mtx3_6 *mtx, int crow, int ccol)
{
	int		row_index;
	int		row1_index;
	double	celem_val;
	double	felem_val;
	double	correc_fact;

	row_index = crow + 1;
	while (row_index < 3)
	{
		if (!close_enough(mtx->val[row_index][ccol], 0.0))
		{
			row1_index = ccol;
			celem_val = mtx->val[row_index][ccol];
			felem_val = mtx->val[row1_index][ccol];
			if (felem_val == 0.0)
				felem_val = 1.0;
			if (!close_enough(felem_val, 0.0))
			{
				correc_fact = -(celem_val / felem_val);
				mtx3_mult_add(mtx, row1_index, correc_fact, row_index);
			}
		}
		row_index++;
	}
}

static void	col_op(t_mtx3_6 *mtx, int crow, int ccol)
{
	int		col_index;
	int		row1_index;
	double	celem_val;
	double	felem_val;
	double	correc_fact;

	col_index = ccol + 1;
	while (col_index < 3)
	{
		if (!close_enough(mtx->val[crow][col_index], 0.0))
		{
			row1_index = col_index;
			celem_val = mtx->val[crow][col_index];
			felem_val = mtx->val[row1_index][col_index];
			if (felem_val == 0.0)
				felem_val = 1.0;
			if (!close_enough(felem_val, 0.0))
			{
				correc_fact = -(celem_val / felem_val);
				mtx3_mult_add(mtx, row1_index, correc_fact, crow);
			}
		}
		col_index++;
	}
}

static void	invert_alg(t_mtx3_6 *mtx)
{
	int		diag_index;
	int		crow;
	int		ccol;

	diag_index = 0;
	while (diag_index < 3)
	{
		crow = diag_index;
		ccol = diag_index;
		check_max(mtx, crow, ccol);
		row_op(mtx, crow, ccol);
		col_op(mtx, crow, ccol);
		++diag_index;
	}
}

bool	mtx3_invert(t_mtx3 *mtx)
{
	t_mtx3_6	tmp_mtx;
	t_mtx3		left;
	t_mtx3		right;
	bool		complete;
	int			count;

	count = 0;
	complete = false;
	tmp_mtx = mtx3_join_identity(*mtx);
	while (complete == false && count < 100)
	{
		invert_alg(&tmp_mtx);
		mtx3_sep_mtx(tmp_mtx, &left, &right);
		if (mtx3_is_identity(left))
		{
			complete = true;
			*mtx = right;
		}
		++count;
	}
	return (complete);
}
