/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:07:55 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:14:03 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_conf	init(void)
{
	t_conf	init;

	ft_memset(&init, 0, sizeof (t_conf));
	init.w_value = -1;
	init.p_value = -1;
	return (init);
}

static void	update_conf(t_conf *conf)
{
	if (conf->flag.minus || (ft_strchr("uidxX", conf->specifier)
			&& conf->p_value >= 0))
		conf->flag.zero = FALSE;
	if (conf->flag.plus)
		conf->flag.space = FALSE;
}

t_conf	get_conf(const char *format, va_list *ap)
{
	t_conf	conf;
	int		i;

	i = 1;
	conf = init();
	if (*format != '%')
		return (conf.specifier = NO_CONV, conf);
	i += get_flag(format + i, &conf);
	i += get_width(format + i, &conf);
	i += get_precision(format + i, &conf);
	i += get_specifier(format + i, &conf);
	get_value(&conf, &ap);
	get_len(&conf);
	update_conf(&conf);
	return (conf);
}
