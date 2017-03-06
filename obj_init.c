#include "fdf.h"

t_pt		find_iso_coord(t_ev *ev, t_pt point)
{
	if (!ev)
	{
		ft_err_fd(2);
		return (point);
	}
	double z_float;
	z_float = (double)point.z * 2;

	point.iso_x = (point.ortho_x - z_float) / sqrt(2);
	point.iso_y = (point.ortho_x + 2 * point.ortho_y + z_float) / sqrt(6);
	//printf("%f, %f   =   %d, %d\n", point.ortho_x, point.ortho_y, point.x, point.y);
	return (point);
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
	point->iso_x = 0;
	point->iso_y = 0;

	return (1);
}

