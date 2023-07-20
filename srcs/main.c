/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:57:44 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:57:45 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_app	app;

	(void)argc;
	(void)argv;
	if (app_execute(&app) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
