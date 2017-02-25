# include "fdf.h"




static int		my_key_function(int keycode, t_ev *ev)
{
	printf("key event %d occured\n", keycode);
	mlx_pixel_put(MLX, WIN, 300, 300, 0x00FF0000);
	return (0);
}


int		launch_mlx(t_ev *ev)
{
	int x;
	int y;

	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "EH MEH LEEX @ 42");

	y = 50;
	while (y < 150)
	{
		x = 50;
		while (x < 680)
		{
			mlx_pixel_put(ev->mlx, ev->win, x, y, 0xAAFFFFFF);		
			x++;
		}
		y++;
	}
	mlx_key_hook(ev->win, my_key_function, 0);
	mlx_loop(ev->mlx);
	return (1);
}