# include "fdf.h"

int		my_key_function(int keycode, t_ev *ev)
{
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	key_hook_translation(keycode, ev);
	key_hook_zoom(keycode, ev);
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
	mlx_clear_window(ev->mlx, ev->win);
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			mlx_pixel_put(ev->mlx, ev->win, ev->points[i][j].iso_x, ev->points[i][j].iso_y, 0x00FF0F);
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
