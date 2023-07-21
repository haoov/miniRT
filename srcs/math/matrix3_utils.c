/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:04:38 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 13:08:47 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"
#include <math.h>

t_mtx3	mtx3_mult(t_mtx3 mtx1, t_mtx3 mtx2)
{
	t_mtx3	res;
	int		l;
	int		c;
	int		i;

	ft_memset(&res, 0, sizeof (t_mtx3));
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
	res.z = vec.x * m.val[2][0] + vec.y * m.val[2][1] + vec.z * m.val[2][2];
	return (res);
}

void	mtx3_identity(t_mtx3 *mtx)
{
	int	l;
	int	c;

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
