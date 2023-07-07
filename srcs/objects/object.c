#include "object.h"

#define EPSILON 1e-21F

void	set_gtfm(t_obj_lst *obj,t_gtfm gtfm)
{
	obj->gtfm = gtfm;
}

t_obj_lst	*obj_lst_at(t_obj_lst *obj_lst, int index)
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

t_obj_lst	*add_obj(t_obj_lst **obj_lst, t_obj_lst *new)
{
	t_obj_lst	*elem;

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
