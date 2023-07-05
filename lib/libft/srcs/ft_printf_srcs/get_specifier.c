/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:13:22 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:13:49 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_specifier(const char *format, t_conf *conf)
{
	char	*ptr;

	ptr = ft_strchr(SPECIFIERS, format[0]);
	if (ptr == NULL)
		conf->specifier = NO_CONV;
	else
		conf->specifier = *ptr;
	return (1);
}
