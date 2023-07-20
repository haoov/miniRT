/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:06:22 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:09:30 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"
#include <math.h>

t_mtx4	mtx4_mult(t_mtx4 mtx1, t_mtx4 mtx2)
{
	t_mtx4	res;
	int		l;
	int		c;
	int		i;

	ft_memset(&res, 0, sizeof (t_mtx4));
	l = 0;
	while (l < 4)
	{
		c = 0;
		while (c < 4)
		{
			i = 0;
			while (i < 4)
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

t_vec4	mtx4_vec_mult(t_vec4 vec, t_mtx4 m)
{
	t_vec4	res;

	res.x = vec.x * m.val[0][0] + vec.y * m.val[0][1]
		+ vec.z * m.val[0][2] + vec.w * m.val[0][3];
	res.y = vec.x * m.val[1][0] + vec.y * m.val[1][1]
		+ vec.z * m.val[1][2] + vec.w * m.val[1][3];
	res.z = vec.x * m.val[2][0] + vec.y * m.val[2][1]
		+ vec.z * m.val[2][2] + vec.w * m.val[2][3];
	res.w = vec.x * m.val[3][0] + vec.y * m.val[3][1]
		+ vec.z * m.val[3][2] + vec.w * m.val[3][3];
	return (res);
}

t_mtx4	mtx4_identity(t_mtx4 *mtx)
{
	int	l;
	int	c;

	l = 0;
	while (l < 4)
	{
		c = 0;
		while (c < 4)
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
	return (*mtx);
}

bool	close_enough(double val1, double val2)
{
	return (fabs(val1 - val2) < 1e-9);
}
