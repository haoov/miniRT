/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:34:13 by rsabbah           #+#    #+#             */
/*   Updated: 2023/02/10 12:26:31 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getwnb(char const *s, char *sep)
{
	int		wnb;
	int		i;

	i = 0;
	wnb = 0;
	while (s[i])
	{
		if (ft_strchr(sep, s[i]) == NULL)
		{
			wnb++;
			while (s[i] && ft_strchr(sep, s[i]) == NULL)
				i++;
		}
		else
			i++;
	}
	return (wnb);
}

static size_t	ft_getwlen(char const *s, char *sep)
{
	size_t	len;

	len = 0;
	while (s[len] && ft_strchr(sep, s[len]) == NULL)
		len++;
	return (len);
}

static char	**ft_filltab(char **tab, char const *s, char *sep, int wnb)
{
	size_t		wlen;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < wnb)
	{
		while (ft_strchr(sep, s[j]) != NULL)
			j++;
		wlen = ft_getwlen(s + j, sep);
		tab[i] = ft_substr(s, j, wlen);
		if (tab[i] == NULL)
		{
			while (--i >= 0)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		i++;
		j += wlen;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char *sep)
{
	char	**tab;
	int		wnb;

	if (s == NULL)
		return (NULL);
	wnb = ft_getwnb(s, sep);
	tab = (char **)malloc(sizeof (char *) * (wnb + 1));
	if (tab == NULL)
		return (NULL);
	tab = ft_filltab(tab, s, sep, wnb);
	if (tab == NULL)
		return (free(tab), NULL);
	return (tab);
}
