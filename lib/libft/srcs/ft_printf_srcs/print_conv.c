/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:16:15 by rsabbah           #+#    #+#             */
/*   Updated: 2023/01/06 12:50:37 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill(t_conf conf)
{
	int		count;
	char	c;

	count = 0;
	c = ' ';
	if (conf.flag.zero)
		c = '0';
	if (conf.specifier == 's' && conf.value.t_ptr == NULL
		&& (size_t)conf.p_value < conf.len)
		conf.len = 0;
	while (conf.w_value > (int)conf.len)
	{
		count += write(1, &c, 1);
		conf.w_value--;
	}
	return (count);
}

int	print_infos(long nb, t_conf conf)
{
	if ((conf.specifier == 'x' && conf.flag.hash && nb > 0)
		|| conf.specifier == 'p')
		return (write(1, "0x", 2));
	else if (conf.specifier == 'X' && conf.flag.hash && nb > 0)
		return (write(1, "0X", 2));
	else if (ft_strchr("udi", conf.specifier) && nb >= 0 && conf.flag.plus)
		return (write(1, "+", 1));
	else if (ft_strchr("udi", conf.specifier) && nb >= 0 && conf.flag.space)
		return (write(1, " ", 1));
	else if (ft_strchr("di", conf.specifier) && nb < 0)
		return (write(1, "-", 1));
	else
		return (0);
}

int	print_conv(const char *format, t_conf conf)
{
	int		count;
	long	nb;

	count = 0;
	nb = cast(conf);
	if (conf.specifier == '%' || conf.specifier == NO_CONV)
		return (write(1, format, 1));
	if (conf.flag.minus == FALSE)
	{
		if (conf.flag.zero)
			count += print_infos(nb, conf);
		count += fill(conf);
		count += print_value(nb, conf);
	}
	else
	{
		count += print_value(nb, conf);
		count += fill(conf);
	}
	return (count);
}
