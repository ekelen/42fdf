# include "fdf.h"

// Maybe personalized error messages
// Exit empty map
// One point
// first line shorter... probably other things
// Find memory leak

static int		validate_line(char *line)
{
	int i;

	i = 0;
	if (!line)
	{
		ft_err_fd(2);
		return (0);
	}
	while (*(line + i))
	{
		if (!ft_isalnum(*(line + i)) && !ft_isstn(*(line + i)) \
			&& *(line + i) != '-')
		{
			ft_putendl_fd(ERR_LINE, 2);
			free(line);
			return (0);
		}
		i++;
	}
	return (i);
}

static int		store_strmap(char *file, char **strmap)
{
	char *line;
	int fd;
	int i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(ERR_INV, 2);
		return (0);
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (!(validate_line(line)))
			return (0);
		*(strmap + i) = ft_strdup(line);
		free(line);
		i++;
	}
	*(strmap + i) = 0;
	
	return (1);
}


int				read_map(char *file, t_ev *ev)
{
	char *line;
	char **strmap;
	int lines;
	int fd;

	lines = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(ERR_INV, 2);
		return (-1);
	}
	while (get_next_line(fd, &line) == 1)
	{
		lines++;
		free(line);
	}
	ev->iy = lines;
	if (lines == 0)
	{
		ft_putendl_fd(ERR_EMPTY, 2);
		return (-1);
	}
	close(fd);
	if (!(strmap = (char **)malloc(sizeof(char *) * (lines))))
		return (0);

	if (!(store_strmap(file, strmap)))
		return (0);
	if (!(map_init(strmap, ev)))
		return (0);
	free(strmap);
	return (1);
}
