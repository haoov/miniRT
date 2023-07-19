#include "light.h"

t_light	*new_light(void)
{
	t_light	*new;

	new = (t_light *)ft_calloc(1, sizeof(t_light));
	if (new == NULL)
		return (NULL);
	new->pos = vec_create(0.0, -5.0, -5.0);
	new->color = vec_create(1.0, 1.0, 1.0);
	new->illumfct = point_illum;
	new->intensity = 1.0;
	return (new);
}

t_light	*add_light(t_light **light_lst, t_light *new)
{
	t_light	*elem;

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
