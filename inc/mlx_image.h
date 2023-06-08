#ifndef MLX_IMAGE_H
# define MLX_IMAGE_H

# include "libft.h"
# include <inttypes.h>

# define RMASK	0xFF000000
# define GMASK	0xFF0000
# define BMASK	0xFF00

typedef struct s_app t_app;

typedef struct s_img
{
	void	*id;
	char 	*data;
	int		bpp;
	int		ed;
	int		size_x;
	int 	size_y;
	int		bpl;
	void	*dsp_id;
}t_img;

t_img		*img_create(void);
int			img_init(t_img *img, void *dsp_id, int size_x, int size_y);
uint32_t	img_convert_color(double r, double g, double b);
void		img_set_pixel(t_img *img, int x, int y, uint32_t color);
void		img_display(void *win_id, t_img *img, int x, int y);
void		img_destroy(t_img *img);

#endif //MLX_IMAGE_H
