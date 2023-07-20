/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_app.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:36:51 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 09:37:08 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"

void	app_loop(t_app *app);
void	app_event(t_app *app);

int	app_init(t_app *app)
{
	ft_memset(app, 0, sizeof (t_app));
	app->dsp_id = mlx_init();
	if (app->dsp_id == NULL)
	{
		return (FAILURE);
	}
	app->win_id = mlx_new_window(app->dsp_id, SIZE_X, SIZE_Y, "test");
	if (app->win_id == NULL)
	{
		return (FAILURE);
	}
	if (img_init(&app->img, app->dsp_id, SIZE_X, SIZE_Y) == FAILURE)
	{
		app_exit(app);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	app_execute(t_app *app)
{
	if (app_init(app) == FAILURE)
	{
		return (FAILURE);
	}
	if (scene_render(app, &app->scene, &app->img) == FAILURE)
	{
		app_exit(app);
		return (FAILURE);
	}
	img_display(app->win_id, &app->img, 0, 0);
	app_event(app);
	app_loop(app);
	return (SUCCESS);
}

void	app_event(t_app *app)
{
	mlx_hook(app->win_id, 17, 0L, mlx_loop_end, app);
	mlx_hook(app->win_id, 2, 1l << 0, app_key_action, app);
}

void	app_loop(t_app *app)
{
	mlx_loop(app->dsp_id);
	app_exit(app);
}

int	app_exit(t_app *app)
{
	cleanup(app);
	img_destroy(&app->img);
	mlx_destroy_window(app->dsp_id, app->win_id);
	mlx_destroy_display(app->dsp_id);
	free(app->dsp_id);
	return (SUCCESS);
}
