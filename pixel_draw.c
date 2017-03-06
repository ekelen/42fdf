# include "fdf.h"


static double	af(double c)
{
	return ((c < 0 ? -c : c));
}

static int		get_axis(t_line *nl, t_pt pt1, t_pt pt2)
{
	nl->dx = af(pt2.iso_x - pt1.iso_x);
	nl->dy = af(pt2.iso_y - pt1.iso_y);
	if (nl->dx == 0 || nl->dy == 0)
		nl->slope = 0;
	if (nl->dx >= nl->dy)
		nl->axis = 'x';
	else
		nl->axis = 'y';
	return (1);
}

static int		get_start(t_line *nl, t_pt pt1, t_pt pt2)
{
	if (nl->axis == 'x')
	{
		if (pt1.iso_x > pt2.iso_x)
		{
			nl->start = &pt2;
			nl->end = &pt1;
			if (nl->start->iso_y > nl->end->iso_y)
				nl->slope = -1;
			return (1);
		}
		if (pt1.iso_y > pt2.iso_y)
			nl->slope = -1;
		return (1);
	}

	if (nl->axis == 'y')
	{
		if (pt1.iso_y > pt2.iso_y)
		{
			nl->start = &pt2;
			nl->end = &pt1;
			if (nl->start->iso_y > nl->end->iso_y)
				nl->slope = -1;
			return (1);
		}
		if (pt1.iso_x > pt2.iso_x)
			nl->slope = -1;
		return (1);
	}
	return (0);
}


t_line			*line_init(t_pt pt1, t_pt pt2)
{
	t_line *nl;
	if (!(nl = malloc(sizeof(t_line))))
		return (NULL);
	nl->start = &pt1;
	nl->end = &pt2;
	nl->dsum = 0;
	nl->axis = '0';
	nl->slope = 1;
	nl->dx = 0;
	nl->dy = 0;
	get_axis(nl, pt1, pt2);
	get_start(nl, pt1, pt2);
	nl->x1 = nl->start->iso_x;
	nl->y1 = nl->start->iso_y;
	nl->x2 = nl->end->iso_x;
	nl->y2 = nl->end->iso_y;
	return (nl);
}

static int		draw_flatline(t_ev *ev, t_line *nl)
{
	double x;
	double y;
	x = nl->x1;
	y = nl->y1;

	printf("(%.0f, %.f) and (%.f, %.f)\n", nl->x1, nl->y1, nl->x2, nl->y2);

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
	ft_err_fd(2);
	return (0);
}

static int		draw_pos(t_ev *ev, t_line *nl)
{
	if (nl->dy == 0 || nl->dx == 0)
	{
		printf("Shouldn't be here");
		return (0);
	}
	if (nl->axis == 'x' && nl->slope == 1)
	{
		nl->dsum = (nl->dy - nl->dx);
		while (nl->x1 < nl->x2)
		{
			nl->dsum += nl->dy;
			mlx_pixel_put(ev->mlx, ev->win, nl->x1, nl->y1, 0x00FF0000);
			if (nl->dsum > 0)
			{	
				nl->dsum -= nl->dx;
				nl->y1++;
			}
			nl->x1++;
		}
		return (1);
	}
	if (nl->axis == 'y')
	{
		nl->dsum = (nl->dx - nl->dy);
		while (nl->y1 < nl->y2)
		{
			nl->dsum += nl->dx;
			mlx_pixel_put(ev->mlx, ev->win, nl->x1, nl->y1, 0x00FF00FF);
			if (nl->dsum > 0)
			{	
				nl->dsum -= nl->dy;
				nl->x1++;
			}
			nl->y1++;
		}
		return (1);
	}
	ft_err_fd(2);
	return (0);
}

static int		draw_neg(t_ev *ev, t_line *nl)
{
	if (nl->axis == 'x')
	{
		nl->dsum = (nl->dy - nl->dx);
		while (nl->x1 < nl->x2)
		{
			nl->dsum += nl->dy;
			mlx_pixel_put(ev->mlx, ev->win, nl->x1, nl->y1, 0x0000FF00);
			if (nl->dsum > 0)
			{	
				nl->dsum -= nl->dx;
				nl->y1--;
			}
			nl->x1++;
		}
		return (1);
	}
	if (nl->axis == 'y')
	{
		nl->dsum = (nl->dx - nl->dy);
		while (nl->y1 < nl->y2)
		{
			nl->dsum += nl->dx;
			mlx_pixel_put(ev->mlx, ev->win, nl->x1, nl->y1, 0x000000FF);
			if (nl->dsum > 0)
			{	
				nl->dsum -= nl->dy;
				nl->x1--;
			}
			nl->y1++;
		}
		return (1);
	}
	return (0);
}


int			draw(t_ev *ev, t_pt pt1, t_pt pt2)
{
	t_line *nl;
	nl = line_init(pt1, pt2);

	if (nl->dy == 0 || nl->dx == 0)
	{
		nl->slope = 0;
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