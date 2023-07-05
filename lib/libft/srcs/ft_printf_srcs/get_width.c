/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:14:40 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:15:04 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_width(const char *format, t_conf *conf)
{
	int	i;

	i = 0;
	if (format[i] > '0' && format[i] <= '9')
	{
		conf->w_value = ft_atoi(format + i);
		while (ft_isdigit(format[i]))
			i++;
	}
	return (i);
}
