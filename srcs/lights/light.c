#include "light.h"

t_light_lst	*add_light(t_light_lst **light_lst, int type)
{
	t_light_lst	*new;
	t_light_lst	*elem;

	new = (t_light_lst *) ft_calloc(1, sizeof (t_light_lst));
	if (new == NULL)
	{
		return (NULL);
	}
	new->light.intensity = 1.0;
	new->light.color = vec_create(255.0, 255.0, 255.0);
	if (type == POINT)
	{
		new->light.illumfct = point_illum;
	}
	if (*light_lst == NULL)
	{
		*light_lst = new;
	}
	else
	{
		elem = *light_lst;
		while (elem->next != NULL)
		{
			elem = elem->next;
		}
		elem->next = new;
	}
	return (*light_lst);
}

t_light_lst	*light_lst_at(t_light_lst *ligt_lst, int index)
{
	if (ligt_lst == NULL)
	{
		return (NULL);
	}
	while (index > 0)
	{
		ligt_lst = ligt_lst->next;
		--index;
	}
	return (ligt_lst);
}
