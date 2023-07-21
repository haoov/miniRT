/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_app.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:21:13 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:22:24 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_APP_H
# define MLX_APP_H

# include "mlx.h"
# include "mlx_image.h"
# include "scene.h"
# include "camera.h"
# include <X11/keysym.h>

# define SIZE_X	1280
# define SIZE_Y 720

typedef struct s_app
{
	void	*dsp_id;
	void	*win_id;
	t_scene	scene;
	t_img	img;
}t_app;

int	app_exit(t_app *app);
int	app_execute(t_app *app);
int	app_key_action(int key_code, t_app *app);

#endif
