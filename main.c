# include "fdf.h"

int		main(int ac, char **av)
{
	int res;
	t_ev ev;
	char *file;

	file = av[1];
	new_ev(&ev);

	if (ac != 2)
	{
		ft_err_fd(1);
		return (0);
	}
	
	res = read_map(file, &ev);
	if (res == -1)
		return (-1);
	if (!res)
		return (-1);
	else
		return (1);
	return (0);
}
