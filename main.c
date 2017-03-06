# include "fdf.h"


static t_ev	*new_ev(t_ev *ev)
{
	ev->z_max = 0;
	ev->z_min = 0;
	ev->iy = 0;
	ev->ix = -1;
	ev->pt_sum = 0;
	ev->ratio = 0;
	ev->ortho_width = 1;
	ev->ortho_height = 1;
	ev->origin_x = 0;
	ev->origin_y = 0;
	ev->offset_y = 0;
	ev->offset_x = 0;
	ev->padding = 0;
	ev->ortho_scale = 0;
	return (ev);
}



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
