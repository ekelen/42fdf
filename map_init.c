# include "fdf.h"



static int		get_relative_dimensions(t_ev *ev)
{
	ev->origin_x = (WIDTH / 2) - (ev->width / 2);
	ev->origin_y = (HEIGHT / 2) - (ev->height / 2);

	ev->offset_y = (HEIGHT / 2) + (ev->height / 2);
	ev->offset_x = (WIDTH / 2) + (ev->width / 2);
	return (1);
}


static int get_active_screen(t_ev *ev)
{
	ev->ratio = ev->x_len / ev->y_height;
	double x = ev->ratio;
	printf("ev->ratio : %f\n", ev->ratio);
	double y = 1;
	if (x < WIDTH - MARGIN && y < WIDTH - MARGIN)
	{
		while (x < WIDTH - MARGIN && y < WIDTH - MARGIN)
		{
			x *= 2;
			y *= 2;
		}
		x /= 2;
		y /= 2;
	}
	ev->height = y;
	ev->width = x;	
	ev->padding = ev->width / ev->y_height;
	printf("ev->height : %f\n", ev->height);
	printf("ev->width : %f\n", ev->width);
	get_relative_dimensions(ev);
	return (1);
}


static int		get_x_len(t_ev *ev, t_pt **map)
{
	int x_len;
	int row;
	int largest;
	int z_max;
	int z_min;

	x_len = 0;
	row = 0;
	largest = x_len;
	z_min = 0;
	z_max = 0;
	while (row < ev->y_height)
	{
		x_len = 0;
		while (map[row][x_len + 1].x >= 0)
		{
			if (map[row][x_len + 1].z > map[row][x_len].z)
				z_max = map[row][x_len + 1].z;
			if (map[row][x_len + 1].z < map[row][x_len].z)
				z_min = map[row][x_len + 1].z;
				x_len++;
		}
		if (x_len > largest)
			largest = x_len;
		if (z_max > ev->z_max)
			ev->z_max = z_max;
		if (z_min < ev->z_min)
			ev->z_min = z_min;
		row++;
	}
	ev->x_len = x_len + 1;
	ev->points = map;
	get_active_screen(ev);
	return (1);
}
/*
void	create_points(char *row, t_pt ***map, int i, int *j)
{
	printf("map[%d][%d] : %f\n", i, *j, map[i][*j]->x);
		map[i][*j]->x = *j;
		map[i][*j]->y = i;
		map[i][*j]->z = ft_atoi(row);
		printf("%f", map[i][*j]->x);
		free(row);
}
*/


int		map_init(char **strmap, t_ev *ev)
{
	int i;
	int j;
	t_pt **map;
	char **row;

	map = (t_pt **)malloc(sizeof(t_pt *) * ev->y_height);
	i = ev->y_height - 1;
	j = 0;
	while (i >= 0)
	{
		j = 0;
		row = ft_strsplit(strmap[i], ' ');
		while (row[j])
			j++;
		map[i] = (t_pt *)malloc(sizeof(t_pt) * j + 1);
		ev->pt_sum += j;
		j = 0;
		while (row[j])
		{
			map[i][j].x = j;
			map[i][j].y = i;
			map[i][j].z = ft_atoi(row[j]);
			free(row[j]);
			j++;
		}
		map[i][j].x = -1;
		i--;
	}
	get_x_len(ev, map);
	free(row);
	return (1);
}
