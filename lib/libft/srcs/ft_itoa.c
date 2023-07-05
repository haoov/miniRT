/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:08:46 by rsabbah           #+#    #+#             */
/*   Updated: 2022/11/09 10:50:31 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long l)
{
	if (l < 0)
		return (ft_numlen(-l) + 1);
	if (l >= 10)
		return (ft_numlen(l / 10) + 1);
	else
		return (1);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	l;
	int		i;

	l = (long)n;
	i = ft_numlen(l);
	res = (char *)ft_calloc((i + 1), sizeof (char));
	if (res == NULL)
		return (NULL);
	if (l < 0)
	{
		res[0] = '-';
		l = -l;
	}
	res[i] = '\0';
	while (--i >= 0)
	{
		if (i == 0 && res[i] == '-')
			break ;
		res[i] = l % 10 + 48;
		l /= 10;
	}
	return (res);
}
