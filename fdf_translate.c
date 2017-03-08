#include "fdf.h"

static int	fdf_translate(t_ev *ev, double x, double y, double z)
{
	int i = 0;
	int j = 0;

	(void)z;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			ev->points[i][j].iso_x += x;
			ev->points[i][j].iso_y += y;
			j++;
		}
		i++;
	}
	get_xy_minmax(ev);
	get_center(ev);
	render_mlx(ev);
	return (1);
}

static int	fdf_zoom(t_ev *ev, double x, double y, double z)
{
	int i = 0;
	int j = 0;

	(void)z;
	get_center(ev);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			ev->points[i][j].iso_x *= x;
			ev->points[i][j].iso_y *= y;
			j++;
		}
		i++;
	}
	get_xy_minmax(ev);
	fdf_recenter(ev);
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