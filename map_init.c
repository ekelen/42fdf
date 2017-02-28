# include "fdf.h"



static int		get_ortho_dimensions(t_ev *ev, t_pt **map)
{
	ev->ortho_height = ev->y_height * ev->ortho_scale;
	ev->ortho_width = ev->x_len * ev->ortho_scale;

	printf("%f\n", ev->ortho_height);
	printf("%f\n", ev->ortho_width);

	ev->origin_x = 0;
	ev->origin_y = 0;

	ev->offset_y = 600;
	ev->offset_x = 600;
	ev->points = map;
	return (1);
}

static int		get_active_screen(t_ev *ev, t_pt ***points)
{
	int i = 0, j = 0;
	if ((WIDTH - MARGIN) / ev->y_height < (WIDTH - MARGIN) - ev->x_len)
	{
		ev->ortho_scale = (WIDTH-MARGIN) / ev->y_height;
	}
	else
		ev->ortho_scale = (WIDTH - MARGIN) / ev->x_len;
	printf("ortho->scale : %d\n", ev->ortho_scale);
	while (i < ev->y_height)
	{
		j = 0;
		while (j < ev->x_len)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*points)[i][j].ortho_x = (*points)[i][j].x * ev->ortho_scale;
			(*points)[i][j].ortho_y = (*points)[i][j].y * ev->ortho_scale;
			printf("( %.1f, %.1f )", (*points)[i][j].ortho_x, (*points)[i][j].ortho_y);
			j++;
		}
		printf("\n");
		i++;
	}
	get_ortho_dimensions(ev, *points);
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
	printf("index length : %f\n", ev->x_len);
	printf("index height : %f\n", ev->y_height);

	get_active_screen(ev, &map);
	return (1);
}



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
