#include "mlx_app.h"
#include "miniRT.h"

void	cleanup(t_app *app)
{
	t_obj_lst	*elem;
	t_light_lst	*lelem;

	while (app->scene.obj_lst != NULL)
	{
		elem = app->scene.obj_lst->next;
		free(app->scene.obj_lst);
		app->scene.obj_lst = elem;
	}
	while (app->scene.light_lst != NULL)
	{
		lelem = app->scene.light_lst->next;
		free(app->scene.light_lst);
		app->scene.light_lst = lelem;
	}
}

