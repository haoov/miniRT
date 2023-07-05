/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:10 by rsabbah           #+#    #+#             */
/*   Updated: 2022/11/09 13:41:07 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 @brief malloc a substring of the given string
 @param str the string
 @param start the begining of the substring
 @param len the length of the substring
 @return the pointer to the substring
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	size;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		start = slen;
	if (slen < start + len)
		size = slen - start + 1;
	else
		size = len + 1;
	sub = (char *)malloc(sizeof(char) * (size));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, size);
	return (sub);
}
