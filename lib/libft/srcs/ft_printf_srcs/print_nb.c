/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:18:09 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/14 13:04:23 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	cast(t_conf conf)
{
	if (ft_strchr("uxX", conf.specifier))
		return ((unsigned int)conf.value.t_int);
	else if (ft_strchr("di", conf.specifier))
		return ((long)conf.value.t_int);
	else
		return ((long)conf.value.t_ptr);
}

char	*get_base(t_conf conf)
{
	if (conf.specifier == 'X')
		return (HEXM_BASE);
	else if (conf.specifier == 'p' || conf.specifier == 'x')
		return (HEX_BASE);
	else
		return (DEC_BASE);
}

size_t	nblen_base(long nb, char *base)
{
	size_t	blen;

	blen = ft_strlen(base);
	if (nb < 0)
		nb *= -1;
	if (nb >= (int)blen)
		return (nblen_base(nb / blen, base) + 1);
	else
		return (1);
}

int	print_nb(long nb, t_conf conf)
{
	static char	*base;
	size_t		nblen;
	int			count;

	count = 0;
	base = get_base(conf);
	nblen = nblen_base(nb, base);
	if (nb == 0 && conf.p_value == 0)
		return (0);
	if (conf.flag.zero == FALSE)
		count += print_infos(nb, conf);
	while (conf.p_value > (int)nblen)
	{
		count += write(1, "0", 1);
		conf.p_value--;
	}
	count += ft_putnbr_base(nb, base);
	return (count);
}
