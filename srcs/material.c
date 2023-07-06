# include "material.h"

/*t_vec	compute_color(t_obj_lst *obj_lst, t_light_lst *light_lst, t_poi poi,
					   t_ray cam_ray, t_material mat)
{
	(void)obj_lst;
	(void)light_lst;
	(void)poi;
	(void)cam_ray;
	(void)mat;
	t_vec	color = vec_create(0.0, 0.0, 0.0);
	return (color);
}*/

t_vec	compute_diffuse_color(t_obj_lst *obj_lst, t_light_lst *light_lst,
							   t_poi poi, t_vec base_color)
{
	t_vec	diff_color;
	t_vec	color;
	t_vec	rgb;
	double	intensity;
	bool	valid_illum = false;
	bool	illum_found = false;

	//Compute the color due to diffuse illum
	diff_color = vec_create(0.0, 0.0, 0.0);
	rgb = vec_create(0.0, 0.0, 0.0);
	while (light_lst != NULL)
	{
		valid_illum = point_illum(&poi.point, &poi.normal, &color, &intensity,
								  light_lst->light, obj_lst, poi.obj);
		if (valid_illum)
		{
			illum_found = true;
			rgb = vec_add(rgb, vec_mult(color, intensity));
		}
		light_lst = light_lst->next;
	}
	if (illum_found)
	{
		diff_color.x = rgb.x * base_color.x;
		diff_color.y = rgb.y * base_color.y;
		diff_color.z = rgb.z * base_color.z;
	}
	return (diff_color);
}
