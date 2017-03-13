# include "fdf.h"

int		main(int ac, char **av)
{
	int res;
	t_ev ev;
	char *file;
	file = av[1];
	new_ev(&ev);

	if (ac < 2 || ac > 3)
	{
		ft_err_fd(1);
		return (0);
	}
	if (ac == 3)
	{
		if (!(ft_strcmp(av[2], "FREEZE")))
			ev.temp = 1;
		else if (!(ft_strcmp(av[2], "COMBUST")))
			ev.temp = 2;
		else if (!(ft_strcmp(av[2], "EVAPORATE")))
			ev.temp = 3;
		else if (!(ft_strcmp(av[2], "MELT")))
			ev.temp = 4;
		else
		{
			ft_putendl_fd(ERR_CH, 2);
			return (-1);
		}
	}
	res = read_map(file, &ev);
	if (res == -1 || !res)
		return (-1);
	return (0);
}
