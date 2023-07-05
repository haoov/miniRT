/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:00:43 by rsabbah           #+#    #+#             */
/*   Updated: 2022/11/15 16:13:19 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_content(char *content)
{
	int		clen;
	int		nl;
	int		i;

	clen = ft_strlen(content);
	nl = 0;
	while (content[nl] != '\n' && nl < clen)
		nl++;
	i = 0;
	while (content[i + nl] && i + nl < clen)
	{
		content[i] = content[i + nl + 1];
		i++;
	}
	while (i < clen)
		content[i++] = '\0';
}

char	*get_line(char *content)
{
	char	*line;
	int		i;

	i = 0;
	while (content[i] != '\n' && content[i])
		i++;
	line = (char *)ft_calloc(i + 2, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
	{
		line[i] = content[i];
		i++;
	}
	if (content[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*add_content(char *content, char *buffer)
{
	char	*tmp;
	int		i;
	int		j;

	if (!content)
		content = (char *)ft_calloc(1, 1);
	if (!content)
		return (NULL);
	if (!(*buffer) && !(*content))
		return (free(content), NULL);
	tmp = content;
	content = (char *)ft_calloc(ft_strlen(tmp) + ft_strlen(buffer) + 1, 1);
	if (content == NULL)
		return (free(tmp), NULL);
	i = -1;
	while (tmp[++i] != '\0')
		content[i] = tmp[i];
	j = 0;
	while (buffer != NULL && buffer[j] != '\0')
		content[i++] = buffer[j++];
	content[i] = '\0';
	return (free(tmp), content);
}

char	*get_content(int fd, char *content)
{
	char	*buffer;
	int		nb;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	*buffer = '\0';
	nb = 1;
	while (nb > 0 && !ft_strnchr(buffer, '\n', nb))
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb == -1)
			return (free(buffer), NULL);
		buffer[nb] = '\0';
		content = add_content(content, buffer);
	}
	return (free(buffer), content);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	content = get_content(fd, content);
	if (!content)
		return (NULL);
	line = get_line(content);
	if (!line)
		return (NULL);
	clean_content(content);
	return (line);
}
