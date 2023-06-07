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
	app->win_id = mlx_new_window(app->dsp_id, 1280, 720, "test");
	if (app->win_id == NULL)
	{
		return (FAILURE);
	}
	if (img_init(&app->img, app->dsp_id, 1280, 720) == FAILURE)
	{
		img_destroy(&app->img);
		return (FAILURE);
	}
	for (int x = 0; x < 1280; ++x)
	{
		for (int y = 0; y < 720; ++y)
		{
			double red = (double) (x / 1280.0) * 255.0;
			double green = (double) (y / 720.0) * 255.0;
			img_set_pixel(&app->img, x, y, img_convert_color(red, green, 0.0));
		}
	}
	return (SUCCESS);
}

int	app_execute(t_app *app)
{
	if (app_init(app) == FAILURE)
	{
		return (FAILURE);
	}
	img_display(app->win_id, &app->img, 0, 0);
	app_event(app);
	app_loop(app);
	return (SUCCESS);
}

void	app_event(t_app *app)
{
	mlx_hook(app->win_id, 17, 0L, app_exit, app);
	mlx_hook(app->win_id, 2, 1l << 0, app_key_action, app);
}

void	app_loop(t_app *app)
{
	mlx_loop(app->dsp_id);
	mlx_destroy_display(app->dsp_id);
	free(app->dsp_id);
}

int	app_exit(t_app *app)
{
	img_destroy(&app->img);
	mlx_destroy_window(app->dsp_id, app->win_id);
	mlx_loop_end(app->dsp_id);
	return (SUCCESS);
}
