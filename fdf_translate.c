#include "fdf.h"


int			fdf_twist(t_ev *ev)
{


	int i = 0, j = 0;
	int xo = 0, yo = 0;
	int	zo = 0;
	get_xy_minmax(ev);
	get_center_x(ev);
	get_center_y(ev);
	fdf_offset(ev, -ev->iso_ctr_x, -ev->iso_ctr_y);
	static int angle = 10;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{	
			xo = (*ev).points[i][j].ortho_x;
			yo = (*ev).points[i][j].ortho_y;
			zo = (*ev).points[i][j].float_z;
			(*ev).points[i][j].ortho_x = xo;
			(*ev).points[i][j].ortho_y = (cos(angle) * yo) - (sin(angle) * zo);
			(*ev).points[i][j].ortho_y = (sin(angle) * yo) + ((cos(angle) * zo));

			j++;
		}
		i++;
	}
	fdf_offset(ev, ev->iso_ctr_x, ev->iso_ctr_y);
	ev->rotate_opt = 0;
	angle += 10;
	return (1);
}

static int	fdf_awesome(t_ev *ev, double z_up)
{
	ev->z_ratio += z_up;
	render_mlx(ev);
	return (1);
}


static int  fdf_rotate(t_ev *ev)
{
	ev->rotate_opt = 1;
	render_mlx(ev);
	
	return (1);
}

static int	fdf_translate(t_ev *ev, double x, double y, double z)
{
	(void)z;

	ev->offset_x_add += x;
	ev->offset_y_add += y;
		//printf("+++!!!%f, %f\n", ev->offset_x, ev->offset_y);
	render_mlx(ev);
	return (1);
}

static int	fdf_zoom(t_ev *ev, double x, double y, double z)
{
	(void)y;
	(void)z;
	ev->ortho_scale *= x;
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
	if (keycode == 20)
	{
		printf("Zooming!\n");
		fdf_zoom(ev, ZOOM_IN, ZOOM_IN, 0);
	}
	else if (keycode == 21)
		fdf_zoom(ev, ZOOM_OUT, ZOOM_OUT, 0);
	return (1);
}

int		key_hook_boring_rotate(int keycode, t_ev *ev)
{
	if (keycode == 38)
		fdf_rotate(ev);
	else if (keycode == 40)
		fdf_rotate(ev);
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

int		key_hook_twist(int keycode, t_ev *ev)
{
	if (keycode == KEY_FIVE)
	{
		printf("Rotate me!\n");
		ev->rotate_opt = 2;
		render_mlx(ev);
	}
	return (1);
}