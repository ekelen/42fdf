#include "fdf.h"

int		key_hook_translation(int keycode, t_ev *ev)
{
	if (keycode == KEY_UP)
		fdf_translate(ev, 0, MOVE_UP);
	else if (keycode == KEY_DOWN)
		fdf_translate(ev, 0, MOVE_DOWN);
	else if (keycode == KEY_LEFT)
		fdf_translate(ev, MOVE_LEFT, 0);
	else if (keycode == KEY_RIGHT)
		fdf_translate(ev, MOVE_RIGHT, 0);
	return (1);
}

int		key_hook_zoom(int keycode, t_ev *ev)
{
	if (keycode == KEY_PLUS)
		fdf_zoom(ev, ZOOM_IN);
	else if (keycode == KEY_MINUS)
		fdf_zoom(ev, ZOOM_OUT);
	return (1);
}

int		key_hook_rotate(int keycode, t_ev *ev)
{
	if (keycode == KEY_EIGHT)
	{
		ev->rotate_opt = 1;
		DIR = 1;
		render_mlx(ev);
	}
	else if (keycode == KEY_NINE)
	{
		ev->rotate_opt = 1;
		DIR = -1;
		render_mlx(ev);
	}
	ev->rotate_opt = 0;
	return (1);
}

int		key_hook_height(int keycode, t_ev *ev)
{
	if (keycode == KEY_ONE)
		fdf_relief(ev, INCLINE, 1);
	else if (keycode == KEY_TWO)
		fdf_relief(ev, INCLINE, -1);
	return (1);
}