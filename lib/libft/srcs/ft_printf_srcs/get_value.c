/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:14:19 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:14:35 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_value(t_conf *conf, va_list **ap)
{
	if (conf->specifier == '%')
		conf->value.t_int = 0;
	else if (conf->specifier == 's' || conf->specifier == 'p')
		conf->value = (t_value)va_arg(**ap, void *);
	else
		conf->value = (t_value)va_arg(**ap, int);
}
