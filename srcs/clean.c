#include "mlx_app.h"
#include "miniRT.h"

void	cleanup(t_app *app)
{
	t_obj_lst	*elem;
	t_light_lst	*lelem;

	while (app->scene.obj_lst != NULL)
	{
		elem = app->scene.obj_lst->next;
		if (app->scene.obj_lst->has_material
			&& app->scene.obj_lst->material.has_texture)
		{
				img_destroy(&app->scene.obj_lst->material.texture.img);
		}
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

