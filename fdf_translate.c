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
	else
	{
		printf("No valid key pressed\n");
		return(0);
	}
	return (1);
}