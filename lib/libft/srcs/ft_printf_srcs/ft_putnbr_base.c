/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:03:08 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:14:06 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(long nbr, const char *base)
{
	size_t	blen;
	char	c;

	blen = ft_strlen(base);
	if (nbr < 0)
		nbr *= -1;
	c = base[nbr % blen];
	if ((size_t)nbr >= blen)
		return (ft_putnbr_base(nbr / blen, base) + write(1, &c, 1));
	return (write(1, &base[nbr % blen], 1));
}
