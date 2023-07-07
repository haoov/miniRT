#include "object.h"

#define EPSILON 1e-21F

static const t_intfct	fcttab[4] = {
		{sphere_intersect}, {plane_intersect}, {cylinder_intersect},
		{cone_intersect}
};

void	set_gtfm(t_obj *obj,t_gtfm gtfm)
{
	obj->gtfm = gtfm;
}

t_obj_lst	*obj_lst_at(t_obj_lst *obj_lst, int index)
{
	if (obj_lst == NULL)
	{
		return (NULL);
	}
	while (index > 0)
	{
		obj_lst = obj_lst->next;
		--index;
	}
	return (obj_lst);
}

t_obj_lst	*add_obj(t_obj_lst **obj_lst, int type)
{
	t_obj_lst	*new;
	t_obj_lst	*elem;

	new = (t_obj_lst *) ft_calloc(1, sizeof (t_obj_lst));
	if (new == NULL)
	{
		return (NULL);
	}
	new->obj.intfct = fcttab[type].fct;
	if (*obj_lst == NULL)
	{
		*obj_lst = new;
	}
	else
	{
		elem = *obj_lst;
		while (elem->next != NULL)
		{
			elem = elem->next;
		}
		elem->next = new;
	}
	return (*obj_lst);
}
