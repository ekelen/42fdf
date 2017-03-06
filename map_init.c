# include "fdf.h"

static t_pt		find_iso_coord(t_ev *ev, t_pt point)
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


static int		get_active_screen(t_ev *ev, t_pt ***points)
{
	ev->origin_x = 300;
	ev->origin_y = 300;
	int i = 0, j = 0;

	
	if ((WIDTH - MARGIN) / ev->iy < (WIDTH - MARGIN) / ev->ix)
		ev->ortho_scale = (WIDTH-MARGIN) / ev->iy;
	else
		ev->ortho_scale = (WIDTH - MARGIN) / ev->ix;
	ev->ortho_scale /= 2;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix && (*points)[i][j].x >= 0)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*points)[i][j].ortho_x = ev->origin_x + (((*points)[i][j].x) * ev->ortho_scale);
			(*points)[i][j].ortho_y = ev->origin_y + (((*points)[i][j].y) * ev->ortho_scale);
			(*points)[i][j] = find_iso_coord(ev, (*points)[i][j]);
			j++;
		}
		i++;
	}
	launch_mlx(ev, *points);
	return (1);
}


static int		get_z_minmax(t_ev *ev, t_pt **points)
{
	int j;
	int i;
	ev->z_max = points[0][0].z;
	ev->z_min = points[0][0].z;

	j = 0;
	i = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (points[i][j].x >= 0)
		{
			if (points[i][j].z > ev->z_max)
				ev->z_max = points[i][j].z;
			if (points[i][j].z < ev->z_min)
				ev->z_min = points[i][j].z;
				j++;
		}
		i++;
	}
	ev->z_range = ft_extra_abs(ev->z_max - ev->z_min);
	get_active_screen(ev, &points);
	return (1);
}



int		map_init(char **strmap, t_ev *ev)
{
	int i;
	int j;
	t_pt **map;
	char **row;

	map = (t_pt **)malloc(sizeof(t_pt *) * ev->iy);
	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		row = ft_strsplit(strmap[i], ' ');
		while (row[j])
			j++;
		map[i] = (t_pt *)malloc(sizeof(t_pt) * j + 1);
		ev->pt_sum += j;
		j = 0;
		while (row[j])
		{
			point_init(&map[i][j], row[j], i, j);
			free(row[j]);
			j++;
		}
		ev->ix = j > ev->ix ? j : ev->ix;
		map[i][j].x = -1;
		i++;
	}
	get_z_minmax(ev, map);
	free(row);
	return (1);
}
