#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"
# include "vector.h"

typedef struct s_sreen
{
	t_vec	u;
	t_vec	v;
	t_vec	c;
}t_screen;

typedef struct s_cam
{
	t_vec		pos;
	t_vec		look_at;
	t_vec		up;
	t_vec		align;
	double		dist;
	double		size;
	double		ratio;
	t_screen	scr;
}t_cam;

void	cam_init(t_cam *cam);
void	cam_set_pos(t_cam *cam, t_vec pos);
void	cam_set_look_at(t_cam *cam, t_vec look_at);
void	cam_set_up(t_cam *cam, t_vec up_vec);
void	cam_set_dist(t_cam *cam, double dist);
void	cam_set_size(t_cam *cam, double size);
void	cam_set_ratio(t_cam *cam, double ratio);
void	cam_geometry(t_cam *cam);
t_ray	cam_generate_ray(t_cam *cam, float x, float y);

#endif //CAMERA_H
