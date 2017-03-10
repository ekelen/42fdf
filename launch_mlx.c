# include "fdf.h"

static int	mix_color(t_ev *ev, t_color *color)
{
	(void)ev;
	int color_int;
	color_int = 0;
	color_int += ((unsigned char)color->r);
	color_int *= 256;
	color_int += ((unsigned char)color->g);
	color_int *= 256;
	color_int += ((unsigned char)color->b);
	return (color_int);
}

int	test_color(t_ev *ev, double height, double z)
{
	int color_int = 0;
	t_color *color;
	color = (t_color *)malloc(sizeof(t_color));
	color_init(color);
	color->r = 0;
	color->g = 0;
	color->b = height ? (255 / z) : 50;
	//printf("Height : %f, Where : %f\n", height, z);
	//printf("color b : %i", color->b);
	//color->a = 200;
	color_int = mix_color(ev, color);
	//printf("Value : %#x (%d)\n", color_int, color_int);
	free(color);
	return (color_int);
}

int		my_key_function(int keycode, t_ev *ev)
{
	if (keycode == KEY_ESC)
		exit(0);
	key_hook_translation(keycode, ev);
	key_hook_rotate(keycode, ev);
	key_hook_zoom(keycode, ev);
	key_hook_height(keycode, ev);
	//key_hook_twist(keycode, ev);
	return (1);
}

static int		optional_rotate(t_ev *ev)
{
	int i;
	int j;
	double xo;
	double yo;
	static double angle = 5;

	i = 0;
	j = 0;
	get_xy_minmax(ev);
	fdf_offset(ev, -ev->iso_ctr_x, -ev->iso_ctr_y);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{	
			xo = (*ev).points[i][j].iso_x;
			yo = (*ev).points[i][j].iso_y;
			(*ev).points[i][j].iso_x = (cos(angle * ev->dir) * xo) - (sin(angle * ev->dir) * yo);
			(*ev).points[i][j].iso_y = (sin(angle * ev->dir) * xo) + (cos(angle * ev->dir) * yo);
			j++;
		}
		i++;
	}
	fdf_offset(ev, ev->iso_ctr_x, ev->iso_ctr_y);
	
	angle += 5;
	return (1);
}

int		render_mlx(t_ev *ev)
{
	int i;
	int j;

	//int c;

	if (!ev)
	{
		ft_err_fd(2);
		return(0);
	}
	j = 0;
	i = 0;
	get_ortho_coords(ev);
	get_new_iso(ev);
	ev->offset_x = fabs(ev->xmin) + ((ev->sw - ev->xrange) / 2) + ev->offset_x_add;
	ev->offset_y = fabs(ev->ymin) + ((ev->sw - ev->yrange) / 2) + ev->offset_y_add;
	fdf_offset(ev, ev->offset_x, ev->offset_y);
	if (ev->rotate_opt == 1)
		optional_rotate(ev);
	mlx_clear_window(ev->mlx, ev->win);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			
			// for (c=0;c<j;c++)
			// {
			// 	mlx_pixel_put(ev->mlx, ev->win, j, i, test_color(ev, ev->points[i][j]));	
			// }
			if (j < ev->ix - 1)
				draw(ev, ev->points[i][j], ev->points[i][j + 1]);
			if (i < ev->iy - 1)
				draw(ev, ev->points[i][j], ev->points[i + 1][j]);
			j++;
		}
		i++;
	}
	return (1);
}


int		launch_mlx(t_ev *ev)
{
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "FDF");
	render_mlx(ev);
	if (!(mlx_key_hook(ev->win, my_key_function, ev)))
		exit(0);
	mlx_loop(ev->mlx);
	return (1);
}
