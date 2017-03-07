# include "fdf.h"


static int		fdf_init_origin(t_ev *ev, t_pt ***points)
{
	int i;
	int j;
	i = 0;
	ev->yrange = ev->ymax - ev->ymin;
	ev->xrange = ev->xmax - ev->xmin;

	// printf("x range (width) : %d\n", ev->xrange);
	// printf("y range (height) : %d\n", ev->yrange);
	// printf("screen width : %d\n", ev->sw);
	// printf("screen height : %d\n", ev->sh);
	ev->offset_y = (MARGIN / 2) + ft_extra_abs(ev->ymin) + ((ev->sh - ev->yrange) / 2);
	ev->offset_x = (MARGIN / 2) + ft_extra_abs(ev->xmin) + ((ev->sw - ev->xrange) / 2);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix && (*points)[i][j].x >= 0)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*points)[i][j].iso_x += ev->offset_x;
			(*points)[i][j].iso_y += ev->offset_y;
			j++;
		}
		i++;
	}
	ev->origin_x = (*points)[0][0].iso_x;
	ev->origin_y = (*points)[0][0].iso_y;
	if (!(move_pts(ev, *points)))
		return (0);
	return (1);
}

static int		fdf_resize(t_ev *ev, t_pt ***points)
{
	double overflow_x;
	double overflow_y;
	double scale;
	int i;
	int j;

	i = 0;
	j = 0;

	overflow_x = ((double)ev->sw / ft_extra_abs(ev->xmax - ev->xmin));
	overflow_y = ((double)ev->sh / ft_extra_abs(ev->ymax - ev->ymin));
	scale = overflow_x < overflow_y ? overflow_x : overflow_y;

	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix && (*points)[i][j].x >= 0)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*points)[i][j].iso_x *= scale;
			(*points)[i][j].iso_y *= scale;
			j++;
		}
		i++;
	}
	render_mlx(ev);
	return (1);
}

static int		fdf_calc_scale(t_ev *ev, t_pt point)
{
	if (point.iso_x < ev->xmin)
		ev->xmin = point.iso_x;
	if (point.iso_x > ev->xmax)
		ev->xmax = point.iso_x;
	if (point.iso_y < ev->ymin)
		ev->ymin = point.iso_y;
	if (point.iso_y > ev->ymax)
		ev->ymax = point.iso_y;
	return (1);
}



static int		get_active_screen(t_ev *ev, t_pt ***points)
{

	int i = 0, j = 0;

	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix && (*points)[i][j].x >= 0)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*points)[i][j].ortho_x = ev->origin_x + (((*points)[i][j].x) * ev->ortho_scale);
			(*points)[i][j].ortho_y = ev->origin_y + (((*points)[i][j].y) * ev->ortho_scale);
			(*points)[i][j].iso_x = (*points)[i][j].ortho_x - (*points)[i][j].ortho_y;
			(*points)[i][j].iso_y = (*points)[i][j].ortho_x + (*points)[i][j].ortho_y - ((*points)[i][j].float_z * ev->z_ratio);
			fdf_calc_scale(ev, (*points)[i][j]);
			j++;
		}
		i++;
	}
	if (ev->xmax - ev->xmin > ev->sw || ev->ymax - ev->ymin > ev->sh)
	{
		printf("\nWHOA! Resize.\n");
		fdf_resize(ev, points);
	}
	fdf_init_origin(ev, points);
	launch_mlx(ev);
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
	ev->ortho_scale = ev->sw / (ev->ix + ev->iy);
	if (!(ev->z_range = ft_extra_abs(ev->z_max - ev->z_min)))
		ev->z_ratio = 0;
	else
		ev->z_ratio = ev->sw / (ev->z_range * ev->ortho_scale);
	printf("z_max : %d\nz_min: %d\nz_range : %d\nz_ratio : %d\n", ev->z_max, ev->z_min, ev->z_range, ev->z_ratio);
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
