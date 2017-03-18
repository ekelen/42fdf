/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:16:06 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/15 19:29:18 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_offset(t_ev *ev)
{
	ev->offset_x = fabs(IS_XMIN) + ((WIDTH - ev->xrange) / 2) + TX;
	ev->offset_y = (-1 * IS_YMIN) + ((WIDTH - ev->yrange) / 2) + TY;
	return (1);
}

int		shift_temp(t_ev *ev, t_color *color)
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

int		get_ix(t_ev *ev)
{
	if (ev->ix > ev->iy)
		return (ev->ix);
	return (ev->iy);
}

int		get_z_ratio(t_ev *ev)
{
	if (!ev)
		return (0);
	if (!(ev->z_range = fabs(ev->z_max - ev->z_min)) \
		|| ev->ix == 1 || ev->iy == 1)
		ev->z_ratio = 0;
	else
	{
		while ((((WIDTH / (get_ix(ev) * 2) * ZF / 20)) + ev->z_mod) > WIDTH / 4)
		{
			while (fabs(ev->z_mod) > 1)
				ev->z_mod -= (.5 * INC_DIR);
		}
		if (!ev->map)
			ZRA = ((WIDTH / (get_ix(ev) * 2) * ZF / 20)) + ev->z_mod;
		else
			ZRA = ((WIDTH / (get_ix(ev) * 2) * ZF / 20)) + (ev->z_mod * .05);
	}
	return (1);
}
