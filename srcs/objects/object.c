/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:49:39 by raph              #+#    #+#             */
/*   Updated: 2023/07/20 17:49:42 by raph             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	set_gtfm(t_obj *obj, t_gtfm gtfm)
{
	obj->gtfm = gtfm;
}

t_obj	*obj_lst_at(t_obj *obj_lst, int index)
{
	if (obj_lst == NULL)
	{
		return (NULL);
	}
	while (obj_lst != NULL)
	{
		if (index == 0)
			break ;
		--index;
		obj_lst = obj_lst->next;
	}
	return (obj_lst);
}

t_obj	*add_obj(t_obj **obj_lst, t_obj *new)
{
	t_obj	*elem;

	if (new == NULL)
		return (NULL);
	if (*obj_lst == NULL)
		*obj_lst = new;
	else
	{
		elem = *obj_lst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
	}
	return (*obj_lst);
}
