#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "gtfm.h"
# include "libft.h"
# include <stdbool.h>

# define SPHERE	0
# define PLANE	1

typedef struct s_poi		t_poi;
typedef struct s_obj_lst	t_obj_lst;

//Struct to hold th plane data
typedef struct s_plane
{

}t_plane;

//Struct t hold the sphere data
typedef struct s_sphere
{

}t_sphere;

//Union to the object type
typedef union u_obj_type
{
	t_sphere	sphere;
	t_plane		plane;
}t_obj_type;

//Struct to hold the object base data
typedef struct s_obj
{
	t_vec		color;
	t_obj_type	type;
	bool		(*intfct)(t_ray, struct s_poi *poi, t_obj_lst *obj);
	t_gtfm		gtfm;
}t_obj;

//Chained list of objects
typedef struct s_obj_lst
{
	t_obj				obj;
	struct s_obj_lst	*next;
}t_obj_lst;

//Struct to hold the intersection point data
typedef struct s_poi
{
	t_vec		point;
	t_vec		normal;
	t_vec		color;
	t_obj_lst	*obj;
}t_poi;

//Struct to hold the intersection function of each objects
typedef struct s_intfct
{
	bool	(*fct)(t_ray, t_poi *poi, t_obj_lst *obj);
}t_intfct;

t_obj_lst	*add_obj(t_obj_lst **obj_lst, int type);
t_obj_lst	*obj_lst_at(t_obj_lst *obj_lst, int index);

bool	sphere_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj);
bool	plane_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj);

bool	close_enough(double val1, double val2);

#endif //OBJECT_H
