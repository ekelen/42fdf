# include "fdf.h"

int		my_key_function(int keycode, t_ev *ev)
{
	if (keycode == KEY_ESC)
		exit(0);
	key_hook_translation(keycode, ev);
	key_hook_rotate(keycode, ev);
	key_hook_zoom(keycode, ev);
	key_hook_height(keycode, ev);
	return (1);
}

static int		rotate(t_ev *ev)
{
	int i;
	int j;
	double xo;
	double yo;
	static double angle = .10;

	i = 0;
	j = 0;
	get_xy_minmax(ev);
	fdf_offset(ev, -ev->iso_ctr_x, -ev->iso_ctr_y);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			xo = IS_X;
			yo = IS_Y;
			IS_X = (cos(angle * DIR) * xo) - (sin(angle * DIR) * yo);
			IS_Y = (sin(angle * DIR) * xo) + (cos(angle * DIR) * yo);
			j++;
		}
		i++;
	}
	fdf_offset(ev, ev->iso_ctr_x, ev->iso_ctr_y);
	angle += .10;
	return (1);
}

int		render_mlx(t_ev *ev)
{
	int i;
	int j;
	if (!ev)
	{
		ft_err_fd(2);
		return(0);
	}
	j = 0;
	i = 0;
	get_ortho_coords(ev);
	get_new_iso(ev);
	ev->offset_x = fabs(IS_XMIN) + ((WIDTH - ev->xrange) / 2) + ev->trans_const_x;
	ev->offset_y = fabs(IS_YMIN) + ((WIDTH - ev->yrange) / 2) + ev->trans_const_y;
	fdf_offset(ev, ev->offset_x, ev->offset_y);
	if (ev->rotate_opt == 1)
		rotate(ev);
	mlx_clear_window(ev->mlx, ev->win);
	ev->start_true = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			mlx_pixel_put(ev->mlx, ev->win, IS_X, IS_Y, 0x00333333);
			if (j < ev->ix - 1)
				draw(ev, ev->points[i][j], ev->points[i][j + 1]);
			if (i < ev->iy - 1)
				draw(ev, ev->points[i][j], ev->points[i + 1][j]);
			j++;
		}
	//	free(ev->points[i]);
		i++;
	}
	//free(ev->points);
	return (1);
}

int		launch_mlx(t_ev *ev)
{
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "FDF");
	ev->start_true = 1;
	render_mlx(ev);
	if (!(mlx_key_hook(ev->win, my_key_function, ev)))
		exit(0);
	mlx_loop(ev->mlx);
	return (1);
}
