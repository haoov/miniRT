/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:12:45 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:13:15 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_precision(const char *format, t_conf *conf)
{
	int	i;

	i = 0;
	if (format[i] == '.')
	{
		i++;
		conf->p_value = ft_atoi(format + i);
		if (conf->p_value < 0)
			conf->p_value = 0;
		while (ft_isdigit(format[i]))
			i++;
	}
	return (i);
}
