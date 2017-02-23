# include "fdf.h"

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
		if (!ft_isalnum(*(line + i)) && !ft_isstn(*(line + i)))
		{
			ft_err_fd(2);
			return (0);
		}
		i++;
	}
	return (1);
}


static int		store_strmap(char *file, char **strmap)
{
	char *line;
	int fd;
	int i = 0;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (!(validate_line(line)))
		{
			ft_err_fd(2);
			return (0);
		}
		*(strmap + i) = ft_strdup(line);
		i++;
		free(line);
	}
	*(strmap + i) = 0;
	ft_putstrmap(strmap);	// for testing
	if (!(map_init(strmap)))
	{
		ft_err_fd(2);
		return (0);
	}
	return (1);
}


int				read_map(char *file)
{
	char *line;
	char **strmap;
	int lines;
	int fd;

	lines = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		lines++;
		free(line);
	}
	close(fd);
	if (!(strmap = (char **)malloc(sizeof(char *) * lines + 1)))
		return (0);
	if (!(store_strmap(file, strmap)))
	{
		ft_err_fd(2);
		return (0);
	}
	return (1);
}