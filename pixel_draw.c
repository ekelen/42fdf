# include "fdf.h"


static double	af(double c)
{
	return ((c < 0 ? -c : c));
}



static int		get_axis(t_line *nl, t_pt pt1, t_pt pt2)
{
	double x_diff;
	double y_diff;


	x_diff = af(pt2.iso_x - pt1.iso_x);
	y_diff = af(pt2.iso_y - pt1.iso_y);

	nl->dx = x_diff;
	nl->dy = y_diff;

	if (x_diff >= y_diff)
		nl->axis = 'x';
	else
		nl->axis = 'y';
	return (1);
}

static int		get_start(t_line *nl, t_pt pt1, t_pt pt2)
{
	nl->start = &pt1;
	nl->end = &pt2;
	nl->slope = 1;
	if (nl->axis == 'x')
	{
		if (pt1.iso_x > pt2.iso_x)
		{
			printf("Flipping\n");

			nl->start = &pt2;
			nl->end = &pt1;
			printf("y1 : %f\n", nl->start->iso_y);
			printf("y2 : %f\n", nl->end->iso_y);
			if (nl->start->iso_y > nl->end->iso_y)
			{
				printf("changing slope\n");
				nl->slope = -1;
			}
			return (1);
		}
		return (1);
	}

	if (nl->axis == 'y')
	{
		if (pt1.iso_y > pt2.iso_y)
		{
			nl->start = &pt2;
			nl->end = &pt1;
			if (pt1.iso_x > pt2.iso_x)
				nl->slope = -1;
			return (1);
		}
		return (1);
	}
	return (0);
}


t_line			*line_init(t_ev *ev, t_pt pt1, t_pt pt2, int x, int y)
{
	t_line *nl;
	if (!(nl = malloc(sizeof(t_line))))
		return (NULL);
	get_axis(nl, pt1, pt2);
	get_start(nl, pt1, pt2);
	//printf("nl->end->iso_x : %f\n", nl->end->iso_x);
	
	nl->dsum = 0;
	
	nl->x1 = nl->start->iso_x;
	nl->y1 = nl->start->iso_y;

	nl->x2 = nl->end->iso_x;
	nl->y2 = nl->end->iso_y;
	//printf("x1 : %f", nl->x1);
	(void)ev;
	(void)x;
	(void)y;
	// [x] Creates correct number of lines
	// [x] check if start and end have correct data
	// [ ] Check if can handle staright horiz lines
	// [ ] Check for good positive lines
	return (nl);
}

static int		draw_flatline(t_ev *ev, t_line *nl)
{
	double x;
	double y;
	x = nl->start->iso_x;
	y = nl->start->iso_y;

	if (nl->dy == 0)
	{
		while (x < nl->x2)
		{
			mlx_pixel_put(ev->mlx, ev->win, x, y, 0x0000CCFF);
			x++;
		}
		return (1);
	}

	if (nl->dx == 0)
	{
		while (y < nl->y2)
		{
			mlx_pixel_put(ev->mlx, ev->win, x, y, 0x000DD0FF);
			y++;
		}
		return (1);
	}
	return (0);
}

static int		draw_pos(t_ev *ev, t_line *nl)
{
	printf("nl->axis : %c\tnl->slope : %d\n", nl->axis, nl->slope);
	if (nl->axis == 'x')
	{
		nl->dsum = (nl->dy - nl->dx);
		while (nl->x1 < nl->x2)
		{
			nl->dsum += nl->dy;
			if (nl->dsum > 0)
			{	
				nl->dsum -= nl->dx;
				mlx_pixel_put(ev->mlx, ev->win, nl->x1, nl->y1, 0x000000FF);
				nl->y1++;
			}
			nl->x1++;
		}
		return (1);
	}
	return (1);
}

static int		draw_neg(t_ev *ev, t_line *nl)
{
	printf("nl->axis : %c\tnl->slope : %d\n", nl->axis, nl->slope);
	if (nl->axis == 'x')
	{
		nl->dsum = (nl->dy - nl->dx);
		while (nl->x1 < nl->x2)
		{
			nl->dsum += nl->dy;
			if (nl->dsum > 0)
			{	
				nl->dsum -= nl->dx;
				mlx_pixel_put(ev->mlx, ev->win, nl->x1, nl->y1, 0x00CC00FF);
				nl->y1--;
			}
			nl->x1++;
		}
		return (1);
	}
	return (1);
}


int			draw(t_ev *ev, t_pt pt1, t_pt pt2, int x_start, int y_start)
{
	t_line *nl;
	nl = line_init(ev, pt1, pt2, x_start, y_start);

	if (nl->dy == 0 || nl->dx == 0)
	{
		draw_flatline(ev, nl);
		free(nl);
		return (1);
	}

	if (nl->slope == 1)
	{
		draw_pos(ev, nl);
		free(nl);
		return (1);
	}

	if (nl->slope == -1)
	{
		draw_neg(ev, nl);
		free(nl);
		return(1);
	}
	
	return (1);
}