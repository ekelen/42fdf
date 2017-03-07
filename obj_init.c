#include "fdf.h"

int			move_pts(t_ev *ev, t_pt **points)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(ev->points = (t_pt **)malloc(sizeof(t_pt *) * ev->iy)))
		return (0);
	while (i < ev->iy)
	{
		j = 0;
		if (!(ev->points[i] = (t_pt *)malloc(sizeof(t_pt) * ev->ix)))
			return (0);
		while (j < ev->ix)
		{
			ev->points[i][j] = points[i][j];
			j++;
		}
		free(points[i]);
		i++;
	}
	free(points);
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

