#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "gtfm.h"
# include "libft.h"
# include <stdbool.h>

# define SPHERE		0
# define PLANE		1
# define CYLINDER	2
# define CONE		3

typedef struct s_poi		t_poi;
typedef struct s_obj_lst	t_obj_lst;

/*********************OBJECT TYPES********************/

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

/*******************MATERIALS***********************/

typedef struct s_simple_mat
{
	t_vec	color;
	double	reflec;
	double	shiny;
}t_simple_mat;

typedef struct s_material
{
	int		type;
	t_vec	color;
	double	reflec;
	double	shiny;
	int		max_ref_ray;
	int		ref_ray_count;
}t_material;

/*******************OBJECT**************************/

//Struct to hold the object base data
typedef struct s_obj
{
	t_vec		color;
	t_material	material;
	t_obj_type	type;
	bool		(*intfct)(t_ray, t_poi *poi, t_obj_lst *obj);
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

/********************FUNCTION DECLARATION***************/

t_obj_lst	*add_obj(t_obj_lst **obj_lst, int type);
t_obj_lst	*obj_lst_at(t_obj_lst *obj_lst, int index);

bool	sphere_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj);
bool	plane_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj);
bool	cylinder_intersect(t_ray cast_ray, t_poi *poi, t_obj_lst *obj_cur);
bool	cone_intersect(t_ray cast_ray, t_poi *poi, t_obj_lst *obj_cur);

bool	close_enough(double val1, double val2);

#endif //OBJECT_H
