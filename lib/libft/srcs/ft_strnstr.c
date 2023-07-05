/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:25:02 by rsabbah           #+#    #+#             */
/*   Updated: 2022/11/09 15:15:17 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 @brief find the first occurrence of small in big
 @param big the big string
 @param small the small string
*/
char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(small);
	if (big == NULL && len == 0)
		return (NULL);
	if (slen == 0)
		return ((char *)big);
	while (big[i] && i + slen <= len)
	{
		if (!ft_strncmp(big + i, small, slen))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
