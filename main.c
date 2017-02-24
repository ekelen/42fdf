# include "fdf.h"


static t_ev	*new_ev(t_ev *ev)
{

	ev->z_max = 0;
	ev->z_min = 0;
	ev->y_offset = 0;
	ev->x_offset = 0;
	ev->pt_sum = 0;
	ev->points = 0;
	return (ev);
}

// int		my_key_function(int keycode, t_ev *ev)
// {
// 	printf("key event %d occured\n", keycode);
// 	mlx_pixel_put(MLX, WIN, 300, 300, 0x00FF0000);
// 	return (0);
// }

int		main(int ac, char **av)
{
	t_ev *ev;
	char *file;

	file = av[1];
	if (!(ev = (t_ev *)malloc(sizeof(t_ev))))
	{
		ft_err_fd(2);
		return (-1);
	}
	ev = new_ev(ev);

	if (ac != 2)
	{
		ft_err_fd(1);
		return (0);
	}
	if (!(read_map(file, ev)))
		printf("INVALID MAP\n");

	// int x;
	// int y;

	// ev->mlx = mlx_init();
	// ev->win = mlx_new_window(MLX, WIDTH, HEIGHT, "EH MEH LEEX @ 42");

	// y = 50;
	// while (y < 150)
	// {
	// 	x = 50;
	// 	while (x < 680)
	// 	{
	// 		mlx_pixel_put(MLX, WIN, x, y, 0xAAFFFFFF);		
	// 		x++;
	// 	}
	// 	y++;
	// }
	// mlx_key_hook(WIN, my_key_function, 0);
	// mlx_loop(MLX);

	free(ev);
	return (0);
}




// # include "fdf.h"

// static void		zero_pt(t_pt *point)
// {
// 	point->x_pt = 0;
// 	point->y_pt = 0;
// 	point->z_pt = 0;
// }


// t_pt	**map_init(char ***strmap, t_ev *ev)
// {
// 	t_pt	**pt_map;
// 	int i = 0;
// 	int j = 0;

// 	if (!(pt_map = (t_pt **)malloc(sizeof(t_pt *) * MAPH)))
// 		return (NULL);

// 	while (i < MAPH)
// 	{
// 		if (!(*(pt_map + i) = (t_pt *)malloc(sizeof(t_pt) * MAPW)))
// 			return (NULL);
// 		j = 0;
// 		while (j < MAPW && strmap[i][j])
// 		{

// 			zero_pt(&pt_map[i][j]);
// 			pt_map[i][j].x_pt = j;
// 			pt_map[i][j].y_pt = i;
// 			printf("%s\n", strmap[i][j]);
// 			pt_map[i][j].z_pt = ft_atoi(strmap[i][j]);

// 			free(strmap[i][j]);
// 			j++;
// 		}

// 		free(strmap[i]);
// 		i++;
// 	}

// 	ev->map = pt_map;
// 	return (pt_map);
// }