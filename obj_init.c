#include "fdf.h"

static int	new_ev_helper(t_ev *ev)
{
	ev->xrange = 0;
	ev->start_true = 0;
	ev->yrange = 0;
	IS_XMIN = 0;
	IS_YMIN = 0;
	IS_XMAX = 0;
	IS_YMAX = 0;
	ev->iso_ctr_x = WIDTH / 2;
	ev->iso_ctr_y = HEIGHT / 2;
	return (1);
}

t_ev	*new_ev(t_ev *ev)
{	
	ev->z_max = 0;
	ev->z_min = 0;
	ev->z_ratio = 0;
	ev->z_range = 0;
	ev->iy = 0;
	ev->ix = 0;
	ev->offset_y = 0;
	ev->offset_x = 0;
	ev->ortho_scale = 0;
	ev->o_x_off = 0;
	ev->o_y_off = 0;
	ev->zoom_factor = 1;
	ev->z_mod = 0;
	ev->rotate_opt = 0;
	DIR = 1;
	new_ev_helper(ev);
	return (ev);
}

int			color_init(t_color *color)
{
	color->a = 0;
	color->r = 0;
	color->g = 0;
	color->b = 0;
	return (1);
}

int			point_init(t_pt *point, char *row, int i, int j)
{
	if (!point || !row)
		return (0);
	point->x = j;
	point->y = i;
	point->z = ft_atoi(row);
	point->ortho_x = 0;
	point->ortho_y = 0;
	point->float_z = (double)point->z;
	point->iso_x = 0;
	point->iso_y = 0;
	return (1);
}

