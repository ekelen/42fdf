# include "fdf.h"

static int		get_iso_dimensions(t_ev *ev)
{
	ev->yrange = fabs(IS_YMAX - IS_YMIN);
	ev->xrange = fabs(IS_XMAX - IS_XMIN);
	ev->iso_ctr_x = (IS_XMIN + (ev->xrange / 2));
	ev->iso_ctr_y = (IS_YMIN + (ev->yrange / 2));
	return (1);
}

static int	get_ix(t_ev *ev)
{
	if (ev->ix > ev->iy)
		return (ev->ix);
	return (ev->iy);
}

int		get_xy_minmax(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;
	IS_XMIN = IS_X;
	IS_XMAX = IS_X;
	IS_YMAX = IS_Y;
	IS_YMIN = IS_Y;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			if (IS_X < IS_XMIN)
				IS_XMIN = IS_X;
			if (IS_X > IS_XMAX)
				IS_XMAX = IS_X;
			if (IS_Y < IS_YMIN)
				IS_YMIN = IS_Y;
			if (IS_Y > IS_YMAX)
				IS_YMAX = IS_Y;
			j++;
		}
		i++;
	}
	get_iso_dimensions(ev);
	return (1);
}

int		get_z_minmax(t_ev *ev)
{
	int j;
	int i;
	ev->z_max = ev->points[0][0].z;
	ev->z_min = ev->points[0][0].z;

	j = 0;
	i = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			if (ev->points[i][j].z > ev->z_max)
				ev->z_max = ev->points[i][j].z;
			if (ev->points[i][j].z < ev->z_min)
				ev->z_min = ev->points[i][j].z;
				j++;
		}
		i++;
	}
	if (!(ev->z_range = fabs(ev->z_max - ev->z_min)))
		ev->z_ratio = 0;
	else
	{
	 	ev->z_ratio = ((WIDTH / (get_ix(ev) * 2) * ev->zoom_factor) / ev->z_range) + ev->z_mod;
	 	while (ev->z_range * ev->z_ratio > (WIDTH / 4))
	 	{
	 		ev->z_mod -= .8;
	 		ev->z_ratio = ((WIDTH / (get_ix(ev) * 2) * ev->zoom_factor) / ev->z_range) + ev->z_mod;
	 	}
	}
	return (1);
}

int		get_new_iso(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!ev)
		return(0);

	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			IS_X = (OR_X - OR_Y);
			IS_Y = (OR_X + OR_Y - ((*ev).points[i][j].float_z * ev->z_ratio));
			j++;
		}
		i++;
	}
	get_xy_minmax(ev);
	return (1);
}

int		get_ortho_coords(t_ev *ev)
{
	int i;
	int j;
	i = 0;
	j = 0;
	get_z_minmax(ev);
	ev->ortho_scale = WIDTH / (get_ix(ev) * 2) * ev->zoom_factor;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			OR_X = ((*ev).points[i][j].x * ev->ortho_scale) + ev->o_x_off;
			OR_Y = ((*ev).points[i][j].y * ev->ortho_scale) + ev->o_y_off;
			j++;
		}
		i++;
	}
	return (1);
}