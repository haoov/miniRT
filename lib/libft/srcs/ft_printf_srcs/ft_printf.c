/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:59:46 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:02:59 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	moove_index(const char *format, t_conf conf)
{
	int	i;

	i = 0;
	if (conf.specifier == NO_CONV)
		return (1);
	if (format[i++] == '%')
		while (!ft_strchr(SPECIFIERS, format[i]))
			i++;
	i++;
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;
	t_conf	conf;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		conf = get_conf(format + i, &ap);
		count += print_conv(format + i, conf);
		i += moove_index(format + i, conf);
	}
	va_end(ap);
	return (count);
}
