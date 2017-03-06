# include "fdf.h"

static int		get_active_screen(t_ev *ev, t_pt ***points)
{
	ev->origin_x = 300;
	ev->origin_y = 300;
	int i = 0, j = 0;
	if ((WIDTH - MARGIN) / ev->y_height < (WIDTH - MARGIN) / ev->x_len)
		ev->ortho_scale = (WIDTH-MARGIN) / ev->y_height;
	else
		ev->ortho_scale = (WIDTH - MARGIN) / ev->x_len;
	ev->ortho_scale /= 2;
	//printf("ortho->scale : %d\n", ev->ortho_scale);
	while (i < ev->y_height)
	{
		j = 0;
		while (j < ev->x_len && (*points)[i][j].x >= 0)   //multiply by ortho->scale to scale for ortho projection.
		{
			(*points)[i][j].ortho_x = ev->origin_x + (((*points)[i][j].x) * ev->ortho_scale);
			(*points)[i][j].ortho_y = ev->origin_y + (((*points)[i][j].y) * ev->ortho_scale);
			(*points)[i][j] = find_iso_coord(ev, (*points)[i][j]);
			j++;
		}
		//printf("\n");
		i++;
	}
	launch_mlx(ev, *points);
	return (1);
}


static int		get_z_minmax(t_ev *ev, t_pt **map)
{
	int j;
	int i;
	int z_max;
	int z_min;

	j = 0;
	i = 0;
	z_min = 0;
	z_max = 0;
	while (i < ev->y_height)
	{
		j = 0;
		while (map[i][j + 1].x >= 0)
		{
			if (map[i][j + 1].z > map[i][j].z)
				z_max = map[i][j].z;
			if (map[i][j + 1].z < map[i][j].z)
				z_min = map[i][j + 1].z;
				j++;
		}
		if (z_max > ev->z_max)
			ev->z_max = z_max;
		if (z_min < ev->z_min)
			ev->z_min = z_min;
		i++;
	}
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
	i = 0;
	j = 0;
	while (i < ev->y_height)
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
			point_init(&map[i][j], row[j], i, j);
			free(row[j]);
			j++;
		}
		ev->x_len = j > ev->x_len ? j : ev->x_len;
		map[i][j].x = -1;
		i++;
	}
	get_z_minmax(ev, map);
	free(row);
	return (1);
}
