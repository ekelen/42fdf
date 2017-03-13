/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 00:49:11 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 00:50:15 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	shift_temp(t_ev *ev, t_color *color)
{
	if (ev->temp == 1)
		freeze_color(color);
	else if (ev->temp == 2)
		combust_color(color);
	else if (ev->temp == 3)
		evaporate_color(color);
	else if (ev->temp == 4)
		melt_color(color);
	return (1);
}

int		init_limits(t_ev *ev, double iso_x, double iso_y)
{
	ev->ymin = iso_y;
	ev->ymax = iso_y;
	ev->xmin = iso_x;
	ev->xmax = iso_x;
	return (1);
}

int	get_ix(t_ev *ev)
{
	if (ev->ix > ev->iy)
		return (ev->ix);
	return (ev->iy);
}

int		get_z_ratio(t_ev *ev)
{
	if (!(ev->z_range = fabs(ev->z_max - ev->z_min)) \
		|| ev->ix == 1 || ev->iy == 1)
		ev->z_ratio = 0;
	else
	{
		while ((((WIDTH / (get_ix(ev) * 2) * ZF) / ZR) + ev->z_mod) > WIDTH / 4)
		{
			while (fabs(ev->z_mod) > 1)
				ev->z_mod -= (.5 * INC_DIR);
		}
		ev->z_ratio = ((WIDTH / (get_ix(ev) * 2) * ev->zoom_factor) / ev->z_range) + ev->z_mod;
	}
	return (1);
}