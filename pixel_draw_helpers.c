/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_draw_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:22:35 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 10:23:15 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_y_line(t_ev *ev, t_line *nl, t_pt pt1, t_pt pt2)
{
	if (pt1.iso_y > pt2.iso_y)
	{
		nl->start = &pt2;
		nl->end = &pt1;
		nl->z1 = pt2.float_z + (ev->z_min * -1);
		nl->z2 = pt1.float_z + (ev->z_min * -1);
		if (nl->start->iso_x > nl->end->iso_x)
			nl->slope = -1;
		return (1);
	}
	if (pt1.iso_x > pt2.iso_x)
		nl->slope = -1;
	return (1);
}

static int	get_x_line(t_ev *ev, t_line *nl, t_pt pt1, t_pt pt2)
{
	if (pt1.iso_x > pt2.iso_x)
	{
		nl->start = &pt2;
		nl->end = &pt1;
		nl->z1 = pt2.float_z + (ev->z_min * -1);
		nl->z2 = pt1.float_z + (ev->z_min * -1);
		if (nl->start->iso_y > nl->end->iso_y)
			nl->slope = -1;
		return (1);
	}
	if (pt1.iso_y > pt2.iso_y)
		nl->slope = -1;
	return (1);
}

int			get_start(t_ev *ev, t_line *nl, t_pt pt1, t_pt pt2)
{
	if (nl->axis == 'x')
		get_x_line(ev, nl, pt1, pt2);
	else if (nl->axis == 'y')
		get_y_line(ev, nl, pt1, pt2);
	return (1);
}

int			get_axis(t_line *nl, t_pt pt1, t_pt pt2)
{
	nl->dx = fabs(pt2.iso_x - pt1.iso_x);
	nl->dy = fabs(pt2.iso_y - pt1.iso_y);
	if (nl->dx == 0 || nl->dy == 0)
		nl->slope = 0;
	if (nl->dx >= nl->dy)
		nl->axis = 'x';
	else
		nl->axis = 'y';
	return (1);
}
