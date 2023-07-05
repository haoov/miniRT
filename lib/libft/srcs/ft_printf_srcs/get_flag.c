/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:06:56 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:14:00 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static void	set_byte(void *data, uint8_t value, int byte)
{
	uint8_t	*bytes;

	bytes = (uint8_t *)data;
	bytes[byte] = value;
}

int	get_flag(const char *format, t_conf *conf)
{
	int	i;
	int	byte;

	i = 0;
	byte = get_index(FLAGS, format[i]);
	while (byte != -1)
	{
		set_byte(&(conf->flag), 1, byte);
		byte = get_index(FLAGS, format[++i]);
	}
	return (i);
}
