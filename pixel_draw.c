/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:23:33 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 10:23:35 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		draw_bes_x(t_ev *ev, t_line *nl)
{
	int tmp;

	tmp = 0;
	if (nl->axis == 'x')
	{
		nl->dsum = (nl->dy - nl->dx);
		while (X1 < X2)
		{
			nl->dsum += nl->dy;
			mlx_pixel_put(MLX, WIN, X1, Y1, test_color(ev, nl, tmp++, nl->dx));
			if (nl->dsum > 0)
			{
				nl->dsum -= nl->dx;
				Y1 += nl->slope;
			}
			X1++;
		}
		return (1);
	}
	return (0);
}

static int		draw_bes_y(t_ev *ev, t_line *nl)
{
	int tmp;

	tmp = 0;
	if (nl->axis == 'y')
	{
		nl->dsum = (nl->dx - nl->dy);
		while (Y1 < Y2)
		{
			nl->dsum += nl->dx;
			mlx_pixel_put(MLX, WIN, X1, Y1, test_color(ev, nl, tmp++, nl->dy));
			if (nl->dsum > 0)
			{
				nl->dsum -= nl->dy;
				X1 += nl->slope;
			}
			Y1++;
		}
		return (1);
	}
	return (0);
}

static int		draw_bes(t_ev *ev, t_line *nl)
{
	if (nl->axis == 'x')
	{
		if (!(draw_bes_x(ev, nl)))
			return (0);
	}
	else if (nl->axis == 'y')
	{
		if (!(draw_bes_y(ev, nl)))
			return (0);
	}
	return (1);
}

int				draw(t_ev *ev, t_pt pt1, t_pt pt2)
{
	t_line *nl;

	if (!(nl = line_init(ev, pt1, pt2)))
	{
		ft_putendl_fd(ERR_RENDER, 2);
		return (0);
	}
	if (!(draw_bes(ev, nl)))
	{
		ft_putendl_fd(ERR_RENDER, 2);
		return (0);
	}
	free(nl);
	return (1);
}
