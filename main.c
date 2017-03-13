#include "fdf.h"

static int		check_args(t_ev *ev, char *s)
{
	if (!(ft_strcmp(s, "FREEZE")))
		ev->temp = 1;
	else if (!(ft_strcmp(s, "COMBUST")))
		ev->temp = 2;
	else if (!(ft_strcmp(s, "EVAPORATE")))
		ev->temp = 3;
	else if (!(ft_strcmp(s, "MELT")))
		ev->temp = 4;
	else
	{
		ft_putendl_fd(ERR_CH, 2);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	int res;
	t_ev ev;
	char *file;

	file = av[1];
	new_ev(&ev);
	if (ac < 2 || ac > 3)
	{
		ft_putendl_fd(ERR_ARGS, 2);
		return (0);
	}
	if (ac == 3)
	{
		if (!(check_args(&ev, av[2])))
			return (0);
	}
	res = read_map(file, &ev);
	if (res == -1 || !res)
		return (-1);
	return (0);
}
