# include "fdf.h"


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
		map[i] = (t_pt *)malloc(sizeof(t_pt) * j);
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
		i--;
	}
	free(row);
	return (1);
}