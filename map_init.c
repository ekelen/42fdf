# include "fdf.h"

/*
static int		get_active_screen(t_ev *ev)
{
	double  ratio;
	double width;
	double height;
	double max_h;
	double max_w;
	ratio = ev->x_offset / ev->y_offset;
	width = ev->x_offset;
	height = ev->y_offset;
	return (1);
}
*/


static int		get_x_offset(t_ev *ev, t_pt **map)
{
	int x_offset;
	int row;
	int largest;
	int z_max;
	int z_min;

	x_offset = 0;
	row = 0;
	largest = x_offset;
	z_min = 0;
	z_max = 0;
	while (row < ev->y_offset)
	{
		x_offset = 0;
		while (map[row][x_offset + 1].x >= 0)
		{
			if (map[row][x_offset + 1].z > map[row][x_offset].z)
				z_max = map[row][x_offset + 1].z;
			if (map[row][x_offset + 1].z < map[row][x_offset].z)
				z_min = map[row][x_offset + 1].z;
				x_offset++;
		}
		if (x_offset > largest)
			largest = x_offset;
		if (z_max > ev->z_max)
			ev->z_max = z_max;
		if (z_min < ev->z_min)
			ev->z_min = z_min;
		row++;
	}
	ev->x_offset = x_offset + 1;
	ev->points = map;
	printf("ev->x_offset : %d\n", ev->x_offset);
	printf("ev->z_min : %d\n", ev->z_min);
	printf("ev->z_max : %d\n", ev->z_max);
	//get_active_screen(ev);
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

	map = (t_pt **)malloc(sizeof(t_pt *) * ev->y_offset);
	i = ev->y_offset - 1;
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
	get_x_offset(ev, map);
	free(row);
	return (1);
}
