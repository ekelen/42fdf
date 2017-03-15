/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:01:36 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 13:54:42 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		validate_line(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (*(line + i))
	{
		if (!ft_isalnum(*(line + i)) && !ft_isstn(*(line + i)) \
			&& *(line + i) != '-' && *(line + i) != 'x' \
			&& *(line + i) != ',')
		{
			ft_putendl_fd(ERR_LINE, 2);
			free(line);
			return (0);
		}
		if (*(line + i) == '\0')
			return (1);
		i++;
	}
	return (i);
}

static int		store_strmap(char *file, char **strmap)
{
	char	*line;
	int		fd;
	int		i;

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

static int		read_helper(char **strmap, char *file, t_ev *ev)
{
	if (ev->iy == 0)
	{
		ft_putendl_fd(ERR_EMPTY, 2);
		return (0);
	}
	if (!(store_strmap(file, strmap)))
		return (0);
	if (!(map_init(strmap, ev)))
		return (0);
	return (1);
	free(strmap);
}

int				read_map(char *file, t_ev *ev)
{
	char	*line;
	char	**strmap;
	int		lines;
	int		fd;

	lines = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(ERR_INV, 2);
		return (0);
	}
	while (get_next_line(fd, &line) == 1)
	{
		lines++;
		free(line);
	}
	close(fd);
	ev->iy = lines;
	if (!(strmap = (char **)malloc(sizeof(char *) * (ev->iy + 1))))
		return (0);
	if (!(read_helper(strmap, file, ev)))
		return (0);
	return (1);
}
