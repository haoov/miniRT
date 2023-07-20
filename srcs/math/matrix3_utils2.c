/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:05:10 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:05:35 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mtx3_6	mtx3_join_mtx(t_mtx3 mtx1, t_mtx3 mtx2)
{
	t_mtx3_6	res;
	int			l;
	int			c;

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

t_mtx3_6	mtx3_join_identity(t_mtx3 mtx)
{
	t_mtx3_6	res;
	t_mtx3		id_mtx;

	mtx3_identity(&id_mtx);
	res = mtx3_join_mtx(mtx, id_mtx);
	return (res);
}

void	mtx3_sep_mtx(t_mtx3_6 mtx, t_mtx3 *mtx1, t_mtx3 *mtx2)
{
	int	l;
	int	c;

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
