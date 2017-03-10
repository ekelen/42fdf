# include "fdf.h"

int		my_key_function(int keycode, t_ev *ev)
{
	if (keycode == KEY_ESC)
		exit(0);
	key_hook_translation(keycode, ev);
	key_hook_zoom(keycode, ev);
	key_hook_boring_rotate(keycode, ev);
	key_hook_height(keycode, ev);
	key_hook_twist(keycode, ev);
	return (1);
}

static int		optional_rotate(t_ev *ev)
{
	int i = 0, j = 0;
	int xo = 0, yo = 0;
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
			xo = (*ev).points[i][j].iso_x;
			yo = (*ev).points[i][j].iso_y;
			(*ev).points[i][j].iso_x = (cos(angle) * xo) - (sin(angle) * yo);
			(*ev).points[i][j].iso_y = (sin(angle) * xo) + (cos(angle) * yo);

			j++;
		}
		i++;
	}
	fdf_offset(ev, ev->iso_ctr_x, ev->iso_ctr_y);
	ev->rotate_opt = 0;
	angle += 10;
	return (1);
}

int		render_mlx(t_ev *ev)
{
	int i;
	int j;
	static int k = 0;
	if (!ev)
	{
		ft_err_fd(2);
		return(0);
	}
	j = 0;
	i = 0;
	
	get_ortho_coords(ev);
	if (ev->rotate_opt == 2)
		fdf_twist(ev);
	get_new_iso(ev);
	get_xy_minmax(ev);
	if (k == 0)
	{
		if (ev->xmax - ev->xmin > ev->sw || ev->ymax - ev->ymin > ev->sh)
			resize_to_fit(ev);
	}
	ev->offset_x = fabs(ev->xmin) + ((ev->sw - ev->xrange) / 2) + ev->offset_x_add;
	ev->offset_y = fabs(ev->ymin) + ((ev->sw - ev->yrange) / 2) + ev->offset_y_add;
	fdf_offset(ev, ev->offset_x, ev->offset_y);
	if (ev->rotate_opt == 1)
		optional_rotate(ev);

	k = 0;

	mlx_clear_window(ev->mlx, ev->win);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			//mlx_pixel_put(ev->mlx, ev->win, ev->points[i][j].iso_x, ev->points[i][j].iso_y, 255);
			//printf("points[%d][%d] = (%f, %f)\n", i, j, ev->points[i][j].iso_x, ev->points[i][j].iso_y);
			if (j < ev->ix - 1)
			{
				//printf("Draws a line on X axis between:\n[%d][%d] = (%.0f, %.f) and (%.f, %.f)\n", i, j, ev->points[i][j].iso_x, ev->points[i][j].iso_y, ev->points[i][j + 1].iso_x, ev->points[i][j + 1].iso_y);
				draw(ev, ev->points[i][j], ev->points[i][j + 1]);
			}
			if (i < ev->iy - 1)
			{
				//printf("Draws a line on Y axis between:\n[%d][%d] = (%.f, %.f) and (%.f, %.f)\n", i, j, ev->points[i][j].iso_x, ev->points[i][j].iso_y, ev->points[i + 1][j].iso_x, ev->points[i + 1][j].iso_y);
				draw(ev, ev->points[i][j], ev->points[i + 1][j]);
			}
			j++;
		}
		i++;
	}
	return (1);
}


int		launch_mlx(t_ev *ev)
{
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "EH MEH LEEX @ 42");
	render_mlx(ev);
	if (!(mlx_key_hook(ev->win, my_key_function, ev)))
		exit(0);
	mlx_loop(ev->mlx);
	return (1);
}
