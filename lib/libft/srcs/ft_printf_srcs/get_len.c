/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:09:08 by rsabbah           #+#    #+#             */
/*   Updated: 2023/01/06 13:15:28 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	addr_len(unsigned long addr)
{
	if (addr >= 16)
		return (addr_len(addr / 16) + 1);
	else
		return (1);
}

static void	update_len(t_conf **conf, long nb)
{
	if ((*conf)->specifier == 's' && (*conf)->value.t_ptr
		&& (*conf)->p_value >= 0 && (*conf)->p_value < (int)(*conf)->len)
		(*conf)->len = (*conf)->p_value;
	else if (ft_strchr("diuxXp", (*conf)->specifier)
		&& (*conf)->p_value > (int)(*conf)->len)
		(*conf)->len = (*conf)->p_value;
	if ((*conf)->specifier != 'p' && nb < 0)
		(*conf)->len++;
	else if ((*conf)->specifier == 'p' && (*conf)->value.t_ptr)
		(*conf)->len += 2;
	else if (ft_strchr("xX", (*conf)->specifier)
		&& (*conf)->flag.hash && nb > 0)
		(*conf)->len += 2;
	else if (ft_strchr("diu", (*conf)->specifier) && ((*conf)->flag.plus
			|| (*conf)->flag.space))
		(*conf)->len++;
}

void	get_len(t_conf *conf)
{
	long		nb;
	static char	*base;

	nb = cast(*conf);
	base = get_base(*conf);
	if (conf->specifier == 'c')
		conf->len = 1;
	else if (conf->specifier == 's' && conf->value.t_ptr == NULL)
		conf->len = 6;
	else if (conf->specifier == 's')
		conf->len = ft_strlen(conf->value.t_ptr);
	else if (conf->specifier == 'p' && conf->value.t_ptr == NULL)
		conf->len = 5;
	else if (conf->specifier == 'p')
		conf->len = addr_len((unsigned long)conf->value.t_ptr);
	else if (conf->value.t_int == 0 && conf->p_value == 0)
		conf->len = 0;
	else
		conf->len = nblen_base(nb, base);
	update_len(&conf, nb);
}
