#include "fdf.h"


static int	fdf_awesome(t_ev *ev, double z_up)
{
	printf("\n\n\n\n");
	ev->z_ratio += z_up;
	render_mlx(ev);
	return (1);
}

static int	fdf_translate(t_ev *ev, double x, double y)
{
	ev->offset_x_add += x;
	ev->offset_y_add += y;
	render_mlx(ev);
	return (1);
}

static int	fdf_zoom(t_ev *ev, double x)
{
	//printf("\n\n\n\n");
	ev->ortho_scale *= x;
	render_mlx(ev);
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
		ev->dir = 1;
		render_mlx(ev);
	}
	else if (keycode == KEY_NINE)
	{
		ev->rotate_opt = 1;
		ev->dir = -1;
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

// int			fdf_twist(t_ev *ev)
// {
// 	int i = 0, j = 0;
// 	double yo = 0;
// 	double xo = 0;
// 	double	zo = 0;
// 	//get_xy_minmax(ev);
// 	//get_center_x(ev);
// 	//get_center_y(ev);
// 	//printf("Center : %f, %f\n", get_center_x(ev), get_center_y(ev));
// 	//get_o_minmax(ev);
// 	//fdf_offset(ev, -ev->iso_ctr_x, -ev->iso_ctr_y);
// 	ev->o_wd = (ev->ix - 1) * ev->ortho_scale;
// 	ev->o_ht = (ev->iy - 1) * ev->ortho_scale;
// 	printf("Width : %.f\n", ev->o_wd);
// 	//printf("ortho_scale : %.f\nwidth :  %.f\n", ev->ortho_scale, ev->ix);
// 	fdf_o_offset(ev, -(ev->o_wd / 2), -(ev->o_ht / 2));
// 	static double angle = 20;
// 	while (i < ev->iy)
// 	{
// 		j = 0;
// 		while (j < ev->ix)
// 		{	
// 			printf("(%.f, %.f, %.f)\t", (*ev).points[i][j].ortho_x, (*ev).points[i][j].ortho_y, (*ev).points[i][j].float_z * ev->z_ratio);
// 			// xo = (*ev).points[i][j].ortho_x;
// 			// yo = (*ev).points[i][j].ortho_y;
// 			// (*ev).points[i][j].ortho_x = (cos(angle) * xo) - (sin(angle) * yo);
// 			// (*ev).points[i][j].ortho_y = (sin(angle) * xo) + (cos(angle) * yo);
// 			(void)xo;
// 			//printf("(%.f, %.f, %.f)\t", (*ev).points[i][j].ortho_x, (*ev).points[i][j].ortho_y, (*ev).points[i][j].float_z * ev->z_ratio);
// 			yo = (*ev).points[i][j].ortho_y;
// 			zo = (*ev).points[i][j].float_z;
// 			(*ev).points[i][j].ortho_y = (cos(angle) * yo) - (sin(angle) * zo);
// 			(*ev).points[i][j].ortho_y = (sin(angle) * yo) + (cos(angle) * zo);


// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	fdf_o_offset(ev, (ev->o_wd / 2), (ev->o_ht / 2));
// 	ev->rotate_opt = 0;
// 	//angle += 20;
// 	return (1);
// }

// int		key_hook_twist(int keycode, t_ev *ev)
// {
// 	if (keycode == KEY_FIVE)
// 	{
// 		ev->rotate_opt = 2;
// 		render_mlx(ev);
// 	}
// 	return (1);
// }