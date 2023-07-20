/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_key_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:36:28 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 09:36:35 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"

int	app_key_action(int key_code, t_app *app)
{
	if (key_code == XK_Escape)
		return (mlx_loop_end(app->dsp_id));
	return (SUCCESS);
}
