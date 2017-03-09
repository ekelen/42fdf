#include "fdf.h"


static int  fdf_rotate(t_ev *ev, double angle)
{
	int i = 0, j = 0;
	int xo = 0, yo = 0;
	get_xy_minmax(ev);
	get_center_x(ev);
	get_center_y(ev);
	fdf_offset(ev, -ev->iso_ctr_x, -ev->iso_ctr_y);
	
	//printf("Center X : %.f\tCenter Y : %.f\n", get_center_x(ev), get_center_y(ev));
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			
			xo = (*ev).points[i][j].iso_x;
			yo = (*ev).points[i][j].iso_y;

			(*ev).points[i][j].iso_x = (cos(angle) * xo) - (sin(angle) * yo);
			(*ev).points[i][j].iso_y = (sin(angle) * xo) + (cos(angle) * yo);

			j++;
		}
		i++;
	}
	fdf_offset(ev, ev->iso_ctr_x, ev->iso_ctr_y);
	render_mlx(ev);
	
	return (1);
}

static int	fdf_translate(t_ev *ev, double x, double y, double z)
{
	(void)z;
	fdf_offset(ev, x, y);
	render_mlx(ev);
	return (1);
}

static int	fdf_zoom(t_ev *ev, double x, double y, double z)
{
	int i = 0;
	int j = 0;
	double octr_x;
	double octr_y;

	(void)z;

	get_xy_minmax(ev);
	//printf("Center X : %.f\tCenter Y : %.f\n", get_center_x(ev), get_center_y(ev));
	//printf("(%.f, %.f) >>>> (%.f, %.f)\n", ev->xmin, ev->ymin, ev->xmax, ev->ymax);
	octr_x = get_center_x(ev);
	octr_y = get_center_y(ev);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			(*ev).points[i][j].iso_x *= x;
			(*ev).points[i][j].iso_y *= y;
			j++;
		}
		i++;
	}
	get_xy_minmax(ev);
	fdf_offset(ev, octr_x - get_center_x(ev), octr_y - get_center_y(ev));
	render_mlx(ev);
	return (1);
}

int		key_hook_translation(int keycode, t_ev *ev)
{
	if (keycode == KEY_UP)
		fdf_translate(ev, 0, MOVE_UP, 0);
	else if (keycode == KEY_DOWN)
		fdf_translate(ev, 0, MOVE_DOWN, 0);
	else if (keycode == KEY_LEFT)
		fdf_translate(ev, MOVE_LEFT, 0, 0);
	else if (keycode == KEY_RIGHT)
		fdf_translate(ev, MOVE_RIGHT, 0, 0);
	return (1);
}

int		key_hook_zoom(int keycode, t_ev *ev)
{
	if (keycode == KEY_PLUS)
		fdf_zoom(ev, ZOOM_IN, ZOOM_IN, 0);
	else if (keycode == KEY_MINUS)
		fdf_zoom(ev, ZOOM_OUT, ZOOM_OUT, 0);
	return (1);
}

int		key_hook_boring_rotate(int keycode, t_ev *ev)
{
	if (keycode == 38)
		fdf_rotate(ev, 10);
	else if (keycode == 40)
		fdf_rotate(ev, -10);
	return (1);
}

// int		key_hook_height(int keycode, t_ev *ev)
// {
// 	if (keycode == KEY_ONE)
// 		fdf_awesome(ev, HIGHER);
// 	else if (keycode == KEY_TWO)
// 		fdf_awesome(ev, LOWER);
// 	return (1);
// }