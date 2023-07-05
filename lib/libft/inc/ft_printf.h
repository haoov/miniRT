/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:54:08 by rsabbah           #+#    #+#             */
/*   Updated: 2022/12/13 16:21:18 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdint.h>
# include <stddef.h>
# include <stdarg.h>

# define SPECIFIERS "cspdiuxX%"
# define FLAGS "#0+ -"
# define DEC_BASE "0123456789"
# define HEX_BASE "0123456789abcdef"
# define HEXM_BASE "0123456789ABCDEF"
# define TRUE 1
# define FALSE 0
# define NO_CONV -1

typedef uint8_t	t_bool;

typedef union u_value
{
	int		t_int;
	void	*t_ptr;
}t_value;

typedef struct s_flag
{
	t_bool	hash;
	t_bool	zero;
	t_bool	plus;
	t_bool	space;
	t_bool	minus;
}t_flag;

typedef struct s_conf
{
	int		w_value;
	int		p_value;
	char	specifier;
	size_t	len;
	t_flag	flag;
	t_value	value;
}t_conf;

int		ft_printf(const char *format, ...);
int		get_flag(const char *format, t_conf *conf);
int		get_width(const char *format, t_conf *conf);
int		get_precision(const char *format, t_conf *conf);
int		get_specifier(const char *format, t_conf *conf);
int		print_conv(const char *format, t_conf conf);
int		print_infos(long nb, t_conf conf);
int		print_value(long nb, t_conf conf);
int		print_nb(long nb, t_conf conf);
int		print_addr(t_conf conf);
int		ft_putnbr_base(long nbr, const char *base);
long	cast(t_conf conf);
size_t	nblen_base(long nb, char *base);
char	*get_base(t_conf conf);
void	get_value(t_conf *conf, va_list **ap);
void	get_len(t_conf *conf);
t_conf	get_conf(const char *fstr, va_list *ap);

#endif