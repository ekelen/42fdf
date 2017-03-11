#include "fdf.h"


static int	fdf_awesome(t_ev *ev, double z_up)
{
	ev->z_mod += z_up;
	render_mlx(ev);
	return (1);
}

static int	fdf_translate(t_ev *ev, double x, double y)
{
	ev->trans_const_x += x;
	ev->trans_const_y += y;
	render_mlx(ev);
	return (1);
}

static int	fdf_zoom(t_ev *ev, double x)
{
	ev->zoom_factor *= x;
	render_mlx(ev);
	return (1);
}

int	fdf_offset(t_ev *ev, double off_x, double off_y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			IS_X += off_x;
			IS_Y += off_y;
			j++;
		}
		i++;
	}
	ev->offset_x = 0;
	ev->offset_y = 0;
	return (1);
}

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
		fdf_awesome(ev, HIGHER);
	else if (keycode == KEY_TWO)
		fdf_awesome(ev, LOWER);
	return (1);
}