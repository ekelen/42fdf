# include "fdf.h"

int		map_init(char **strmap, t_ev *ev)
{
	int i;
	int j;
	char **row;

	ev->points = (t_pt **)malloc(sizeof(t_pt *) * ev->iy);
	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		row = ft_strsplit(strmap[i], ' ');
		while (row[j])
			j++;
		ev->points[i] = (t_pt *)malloc(sizeof(t_pt) * j);
		j = 0;
		while (row[j])
		{
			point_init(&ev->points[i][j], row[j], i, j);
			free(row[j]);
			j++;
		}
		ev->ix = j;
		i++;
	}
	launch_mlx(ev);
	free(row);
	return (1);
}
