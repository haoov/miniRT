/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:07:11 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:07:25 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mtx4_8	mtx4_join_mtx(t_mtx4 mtx1, t_mtx4 mtx2)
{
	t_mtx4_8	res;
	int			l;
	int			c;

	l = 0;
	while (l < 4)
	{
		c = 0;
		while (c < 8)
		{
			while (c < 4)
			{
				res.val[l][c] = mtx1.val[l][c];
				c++;
			}
			res.val[l][c] = mtx2.val[l][c - 4];
			c++;
		}
		l++;
	}
	return (res);
}

t_mtx4_8	mtx4_join_identity(t_mtx4 mtx)
{
	t_mtx4_8	res;
	t_mtx4		id_mtx;

	mtx4_identity(&id_mtx);
	res = mtx4_join_mtx(mtx, id_mtx);
	return (res);
}

void	mtx4_sep_mtx(t_mtx4_8 mtx, t_mtx4 *mtx1, t_mtx4 *mtx2)
{
	int	l;
	int	c;

	l = 0;
	while (l < 4)
	{
		c = 0;
		while (c < 8)
		{
			while (c < 4)
			{
				mtx1->val[l][c] = mtx.val[l][c];
				c++;
			}
			mtx2->val[l][c - 4] = mtx.val[l][c];
			c++;
		}
		l++;
	}
}

bool	mtx4_is_identity(t_mtx4 mtx)
{
	int	row;
	int	col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
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
