# include "fdf.h"

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
	{
		printf("INVALID MAP\n");
		return (0);
	}
	
	free(ev);
	return (0);
}
