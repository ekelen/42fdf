#include "fdf.h"

static int	fdf_translate(t_ev *ev, t_pt ***points, double x, double y)
{
	int i = 0;
	int j = 0;

	(void)points;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix && ev->points[i][j]->x >= 0)
		{
			ev->points[i][j]->iso_x += x;
			ev->points[i][j]->iso_y += y;
			j++;
		}
		i++;
	}
	return (1);
}

void	key_hook_translation(int keycode, t_ev *ev)
{
	if (keycode == KEY_UP)
		fdf_translate(ev, ev->points, 0, MOVE_UP);
	else if (keycode == KEY_DOWN)
		fdf_translate(ev, ev->points, 0, MOVE_DOWN);
	else if (keycode == KEY_LEFT)
		fdf_translate(ev, ev->points, MOVE_LEFT, 0);
	else if (keycode == KEY_RIGHT)
		fdf_translate(ev, ev->points, MOVE_RIGHT, 0);
}