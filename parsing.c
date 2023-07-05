/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:42:35 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/05 18:28:17 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "libft.h"
#include "object.h"
#include "mlx_app.h"
#include "miniRT.h"

int print_error(char *context, char *str)
{
//	char *tmp;

	ft_putstr_fd("Error: miniRT: ", 2);
	if (context)
	{
//		tmp = ft_strdup(context);
//		tmp[ft_strlen(tmp) - 2] = '\0';
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
//		free(tmp);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (FAILURE);
}

int check_args(t_app *app)
{
	if (app->argc != 2)
		return (print_error(__BASE_FILE__, "Wrong number of arguments"));
	if (ft_strncmp(app->argv[1] + ft_strlen(app->argv[1]) - 3, ".rt", 3))
		return (print_error(__BASE_FILE__, "Wrong file extension"));
	if (ft_strlen(app->argv[1]) < 4)
		return (print_error(__BASE_FILE__, "Wrong file name"));
	return (SUCCESS);
}

int check_file(t_app *app)
{
	int	fd;

	fd = open(app->argv[1], O_RDONLY);
	if (fd == -1)
		return (print_error(__FILE_NAME__, strerror(errno)));
	close(fd);
	return (SUCCESS);
}

int app_parse(t_app *app)
{
	if (check_args(app) == FAILURE)
		return (FAILURE);
	if (check_file(app) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}