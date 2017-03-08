# include "fdf.h"

int		fdf_recenter(t_ev *ev)
{
	int i = 0;
	int j = 0;

	double offset_from_x_ctr;
	double offset_from_y_ctr;

	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			printf("Center : (%f, %f)\n", ev->iso_ctr_x, ev->iso_ctr_y);
			printf("Current : (%f, %f)\n", ev->points[i][j].iso_x, ev->points[i][j].iso_y);


			offset_from_x_ctr = ev->points[i][j].iso_x - ev->iso_ctr_x;
			offset_from_y_ctr = ev->points[i][j].iso_y - ev->iso_ctr_y;
			printf("Move : (%f, %f)\n", offset_from_x_ctr, offset_from_y_ctr);
			ev->points[i][j].iso_x -= offset_from_x_ctr;
			ev->points[i][j].iso_y -= offset_from_y_ctr;
			j++;
		}
		i++;
	}
	return (1);
}

int		get_center(t_ev *ev)
{
	ev->iso_ctr_y = (ev->yrange / 2) + ev->ymin;
	ev->iso_ctr_x = (ev->xrange / 2) + ev->ymin;
	return (1);
}

int		fdf_center(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ev->offset_y = (MARGIN / 2) + ft_extra_abs(ev->ymin) + ((ev->sh - ev->yrange) / 2);
	ev->offset_x = (MARGIN / 2) + ft_extra_abs(ev->xmin) + ((ev->sw - ev->xrange) / 2);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			(*ev).points[i][j].iso_x += ev->offset_x;
			(*ev).points[i][j].iso_y += ev->offset_y;
			j++;
		}
		i++;
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
		while (j < ev->ix)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*ev).points[i][j].iso_x = (*ev).points[i][j].ortho_x - (*ev).points[i][j].ortho_y;
			(*ev).points[i][j].iso_y = (*ev).points[i][j].ortho_x + (*ev).points[i][j].ortho_y - ((*ev).points[i][j].float_z * ev->z_ratio);
			j++;
		}
		i++;
	}
	return (1);
}

int		get_xy_minmax(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;

	ev->xmin = ev->points[i][j].iso_x;
	ev->xmax = ev->points[i][j].iso_x;
	ev->ymax = ev->points[i][j].iso_y;
	ev->ymin = ev->points[i][j].iso_y;
	
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			if (ev->points[i][j].iso_x < ev->xmin)
				ev->xmin = ev->points[i][j].iso_x;
			if (ev->points[i][j].iso_x > ev->xmax)
				ev->xmax = ev->points[i][j].iso_x;
			if (ev->points[i][j].iso_y < ev->ymin)
				ev->ymin = ev->points[i][j].iso_y;
			if (ev->points[i][j].iso_y > ev->ymax)
				ev->ymax = ev->points[i][j].iso_y;
			j++;
		}
		i++;
	}
	ev->yrange = ev->ymax - ev->ymin;
	ev->xrange = ev->xmax - ev->xmin;
	return (1);
}

int		get_ortho_coords_from_scale(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*ev).points[i][j].ortho_x = (*ev).points[i][j].x * ev->ortho_scale;
			(*ev).points[i][j].ortho_y = (*ev).points[i][j].y * ev->ortho_scale;
			j++;
		}
		i++;
	}
	return (1);
}