/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:47:15 by rsabbah           #+#    #+#             */
/*   Updated: 2022/11/09 13:43:17 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = (unsigned int)ft_strlen(s1);
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	while (end > 0 && ft_isset(s1[end - 1], set))
		end--;
	res = ft_substr(s1, start, end - start);
	return (res);
}
