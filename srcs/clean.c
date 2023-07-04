#include "mlx_app.h"
#include "miniRT.h"

void	cleanup(t_app *app)
{
	t_obj_lst	*elem;

	while (app->scene.obj_lst != NULL)
	{
		elem = app->scene.obj_lst->next;
		free(app->scene.obj_lst);
		app->scene.obj_lst = elem;
	}
}

