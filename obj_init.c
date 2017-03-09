#include "fdf.h"

t_ev	*new_ev(t_ev *ev)
{	
	ev->sw = WIDTH;
	ev->sh = HEIGHT;

	ev->z_max = 0;
	ev->z_min = 0;
	ev->z_ratio = 0;
	ev->z_range = 0;

	ev->xrange = 0;
	ev->yrange = 0;

	ev->xmin = 0;
	ev->ymin = 0;
	ev->xmax = 0;
	ev->ymax = 0;

	ev->iy = 0;
	ev->ix = 0;
	
	ev->origin_x = 0;
	ev->origin_y = 0;

	ev->iso_ctr_x = ev->sw / 2;
	ev->iso_ctr_y = ev->sh / 2;

	ev->offset_y = 0;
	ev->offset_x = 0;
	
	ev->ortho_scale = 0;

	return (ev);
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

