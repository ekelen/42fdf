# include "fdf.h"

/*
static int		my_key_function(int keycode, t_ev *ev)
{
	printf("key event %d occured\n", keycode);
	mlx_pixel_put(MLX, WIN, 300, 300, 0x00FF0000);
	return (0);
}
*/

// static double	af(double c)
// {
// 	return ((c < 0 ? -c : c));
// }


// static int		draw(t_ev *ev, t_pt pt1, t_pt pt2, int x1, int y1)
// {
// 	if (!ev)
// 		return (0);

	
// 	double dx;
// 	double dy;
// 	double axis;
// 	double dy_sum;

// 	axis = 0;
// 	dx = pt2.iso_x - pt1.iso_x;
// 	dy = pt2.iso_y - pt1.iso_y;

// 	printf("dx : %.1f\n", dx);
// 	printf("dy : %.1f\n", dy);

// 	if (dx == 0)
// 	{
// 		while (y1 < pt2.iso_y)
// 		{
// 			mlx_pixel_put(ev->mlx, ev->win, x1, y1, 0x00FF00FF);
// 			y1++;
// 		}
// 		return (1);
// 	}

// 	else if (dy == 0)
// 	{
// 		while (x1 < pt2.iso_x)
// 		{
// 			mlx_pixel_put(ev->mlx, ev->win, x1, y1, 0x0000000F);
// 			x1++;
// 		}
// 		return (1);
// 	}

// 	if (af(dx) >= af(dy))
// 	{
// 		if (pt1.iso_x < pt2.iso_x)
// 		{
// 			t_pt tmp;
// 			tmp = pt1;
// 			pt1 = pt2;
// 			pt2 = pt1;
// 		}
// 		dx = pt2.iso_x - pt1.iso_x;
// 		dy = pt2.iso_y - pt1.iso_y;
// 		dy_sum = dx / 2;

// 		while (x1 < pt2.iso_x)
// 		{
// 			dy_sum += dy;
// 			if (dy_sum > dx)
// 			{
// 				dy_sum -= dx;
// 				mlx_pixel_put(ev->mlx, ev->win, x1, y1, 0x00FF03FF);
// 				y1++;
// 			}
// 			x1++;
// 		}

// 		return (1);
// 	}

// 	// if (abs_dx < abs_dy)
// 	// {
// 	// 	if (dx < 0 || dy < 0)
// 	// 	{
// 	// 		printf("Negative line!\n");
// 	// 		return(0);
// 	// 	}
// 	// 	dy_sum = dy / 2;

// 	// 	while (y1 < pt2.iso_y)
// 	// 	{
// 	// 		dy_sum += dx;
// 	// 		if (dy_sum > dy)
// 	// 		{
// 	// 			dy_sum -= dy;
// 	// 			mlx_pixel_put(ev->mlx, ev->win, x1, y1, 0x0000FFFF);
// 	// 			x1++;
// 	// 		}
// 	// 		y1++;
// 	// 	}
// 	// 	return (1);
// 	// }

// 	else https://open.spotify.com/user/youzoun/playlist/2POsysj8dTuOCAMPYVsgeO
// 	printf("Didn't draw a line this time.\n");
// 	return (0);
	
// }

int		launch_mlx(t_ev *ev, t_pt **points)
{
	int i;
	int j;

	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "EH MEH LEEX @ 42");

	j = 0;
	i = 0;

	//mlx_pixel_put(ev->mlx, ev->win, points[i][j].iso_x, points[i][j].iso_y, 0x00FF0F);

	while (i < ev->y_height)
	{
		j = 0;
		while (j <= ev->x_len && points[i][j].x >= 0)
		{
			mlx_pixel_put(ev->mlx, ev->win, points[i][j].iso_x, points[i][j].iso_y, 0x00FF0F);
			//printf("points[%d][%d] = (%f, %f)\n", i, j, points[i][j].iso_x, points[i][j].iso_y);
			if (points[i][j + 1].x >= 0)
			{
				//printf("Horizontal line.");
				draw(ev, points[i][j], points[i][j + 1], points[i][j].iso_x, points[i][j].iso_y);
			}
			if (i < ev->y_height - 1)
			{
				//printf("Vertical line.");
				draw(ev, points[i][j], points[i + 1][j], points[i][j].iso_x, points[i][j].iso_y);
			}
			j++;
		}
		i++;
	}
	//mlx_key_hook(ev->win, my_key_function, 0);
	mlx_loop(ev->mlx);
	return (1);
}
