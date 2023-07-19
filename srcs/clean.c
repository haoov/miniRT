#include "mlx_app.h"
#include "miniRT.h"

void	cleanup(t_app *app)
{
	t_obj	*elem;
	t_light	*lelem;

	while (app->scene.obj_lst != NULL)
	{
		elem = app->scene.obj_lst->next;
		if (app->scene.obj_lst->has_mat
			&& app->scene.obj_lst->mat.has_texture)
		{
				img_destroy(&app->scene.obj_lst->mat.texture.img);
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

