#include "camera.h"
#include "ray.h"

#include <stdio.h>

void	cam_init(t_cam *cam)
{
	cam->pos = vec_create(0.0, 0.0, -10.0);
	cam->up = vec_create(0.0, 1.0, 0.0);
	cam->dist = 1;
	cam->size = 1;
	cam->ratio = 1;
}

void	cam_geometry(t_cam *cam)
{
	cam->align = vec_sub(cam->look_at, cam->pos);
	vec_normalize(&cam->align);
	cam->scr.u = vec_cross(cam->align, cam->up);
	vec_normalize(&cam->scr.u);
	cam->scr.v = vec_cross(cam->scr.u, cam->align);
	vec_normalize(&cam->scr.v);
	cam->scr.c = vec_add(cam->pos, vec_mult(cam->align, cam->dist));
	cam->scr.u = vec_mult(cam->scr.u, cam->size);
	cam->scr.v = vec_mult(cam->scr.v, cam->size / cam->ratio);
}

t_ray	cam_generate_ray(t_cam *cam, float x, float y)
{
	t_vec	scr_vec1;
	t_vec	pcdt;

	scr_vec1 = vec_add(cam->scr.c, vec_mult(cam->scr.u, x));
	pcdt = vec_add(scr_vec1, vec_mult(cam->scr.v, y));
	return (ray_create(cam->pos, pcdt));
}
