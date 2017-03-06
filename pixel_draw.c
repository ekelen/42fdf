# include "fdf.h"


static double	af(double c)
{
	return ((c < 0 ? -c : c));
}

static char		get_axis(t_pt pt1, t_pt pt2)						// Get dominant axis for line draw
{
	char axis;
	double diff_x;
	double diff_y;

	axis = 'y';
	diff_x = pt2.iso_x - pt1.iso_x;
	diff_y = pt2.iso_y - pt1.iso_y;
	if (af(diff_x) >= af(diff_y))
		axis = 'x';
	return (axis);
}

static int			get_rel_pt(t_pt pt1, t_pt pt2, t_pt *start, t_pt *end)	// Get start and end point for line draw
{
	char axis;
	axis = get_axis(pt1, pt2);
	printf("axis : %c\n", axis);

	*start = pt1;
	*end = pt2;

	if (pt2.iso_x < pt1.iso_x && pt2.iso_y < pt1.iso_y)
	{
		*start = pt2;
		*end = pt1;
		return (2);
	}
	if (axis == 'x' && pt2.iso_x < pt1.iso_x)
	{
		*start = pt2;
		*end = pt1;
		return (2);
	}
	if (axis == 'y' && pt2.iso_y < pt1.iso_y)
	{
		*start = pt2;
		*end = pt1;
		return (2);
	}
	return (1);
}

int			draw(t_ev *ev, t_pt pt1, t_pt pt2, int x_start, int y_start)
{
	t_pt *start;
	t_pt *end;

	start = (t_pt *)malloc(sizeof(t_pt));
	end = (t_pt *)malloc(sizeof(t_pt));
	get_rel_pt(pt1, pt2, start, end);
	printf("start x/y : %f, %f\n", start->iso_x, start->iso_y);
	(void)ev;
	(void)x_start;
	(void)y_start;
	return (1);
}