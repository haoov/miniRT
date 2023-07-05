/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:20:01 by rsabbah           #+#    #+#             */
/*   Updated: 2023/01/06 12:31:21 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_null(t_conf conf)
{
	if (conf.specifier == 'p')
		return (write(1, "(nil)", 5));
	else if (conf.specifier == 's' && (size_t)conf.p_value >= conf.len)
		return (write(1, "(null)", 6));
	else
		return (0);
}

int	print_value(long nb, t_conf conf)
{
	if (ft_strchr("sp", conf.specifier) && conf.value.t_ptr == NULL)
		return (print_null(conf));
	else if (conf.specifier == 'c')
		return (write(1, &conf.value.t_int, 1));
	else if (conf.specifier == 's')
		return (write(1, conf.value.t_ptr, conf.len));
	else if (conf.specifier == 'p')
		return (print_addr(conf));
	else
		return (print_nb(nb, conf));
}
