/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:00:51 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 14:00:57 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		validate_rectangle(t_ev *ev, int i, int j)
{
	static int start = 1;

	if ((i >= 300 || j >= 300) && start)
	{
		ft_putendl_fd(ERR_SIZE, 2);
		start--;
		return (0);
	}
	if (start)
	{
		if (i == 0)
			ev->ix = j;
		else
		{
			if (j != ev->ix && start)
			{
				ft_putendl_fd(ERR_JAGGED, 2);
				start--;
				return (0);
			}
		}
		return (1);
	}
	return (1);
}

static int		point_init_caller(t_ev *ev, char **row, int i, int *j)
{
	while (row[*j])
	{
		point_init(&ev->points[i][*j], row[*j], i, *j);
		free(row[*j]);
		(*j)++;
	}
	free(row);
	return (1);
}

int				map_init(char **strmap, t_ev *ev)
{
	int		i;
	int		j;
	char	**row;

	if (!(ev->points = (t_pt **)malloc(sizeof(t_pt *) * ev->iy)))
		return (0);
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
		point_init_caller(ev, row, i, &j);
		free(strmap[i]);
		if (!(validate_rectangle(ev, i, j)))
			return (0);
		i++;
	}
	free(strmap[i]);
	launch_mlx(ev);
	return (1);
}
