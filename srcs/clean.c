/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:57:24 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:57:32 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"

void	cleanup(t_app *app)
{
	t_obj	*elem;
	t_light	*lelem;

	while (app->scene.obj_lst != NULL)
	{
		elem = app->scene.obj_lst->next;
		if (app->scene.obj_lst->has_mat)
		{
			if (app->scene.obj_lst->mat.has_texture)
				img_destroy(&app->scene.obj_lst->mat.texture.img);
			if (app->scene.obj_lst->mat.has_nmap)
				img_destroy(&app->scene.obj_lst->mat.nmap.img);
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
