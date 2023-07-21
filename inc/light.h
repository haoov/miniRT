/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:19:26 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 11:19:55 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "ray.h"
# include "object.h"
# include "libft.h"
# include <stdbool.h>

typedef struct s_scene	t_scene;

typedef struct s_light
{
	t_vec			color;
	t_vec			pos;
	double			intensity;
	struct s_light	*next;
}t_light;

t_light	*new_light(void);
t_light	*add_light(t_light **light_lst, t_light *new);
bool	illum(t_scene scene, t_poi *poi, t_light light);

#endif
