/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:02:37 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 14:02:39 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	new_ev_helper(t_ev *ev)
{
	ev->xrange = 0;
	ev->start_true = 0;
	ev->yrange = 0;
	IS_XMIN = 0;
	IS_YMIN = 0;
	IS_XMAX = 0;
	IS_YMAX = 0;
	ev->iso_ctr_x = WIDTH / 2;
	ev->iso_ctr_y = HEIGHT / 2;
	ev->incline_dir = 0;
	ev->trans_const_x = 0;
	ev->trans_const_y = 0;
	ev->temp = 0;
	ev->map = 0;
	return (1);
}

t_ev		*new_ev(t_ev *ev)
{
	ev->z_max = 0;
	ev->z_min = 0;
	ev->z_ratio = 0;
	ev->z_range = 0;
	ev->iy = 0;
	ev->ix = 0;
	ev->offset_y = 0;
	ev->offset_x = 0;
	ev->ortho_scale = 0;
	ev->o_x_off = 0;
	ev->o_y_off = 0;
	ev->zoom_factor = 1;
	ev->z_mod = 0;
	ev->rotate_opt = 0;
	DIR = 1;
	new_ev_helper(ev);
	return (ev);
}

int			color_init(t_color *color)
{
	color->a = 0;
	color->r = 255;
	color->g = 255;
	color->b = 255;
	color->rbase = 0;
	color->gbase = 0;
	color->bbase = 0;
	color->r_rg = 255;
	color->g_rg = 255;
	color->b_rg = 255;
	return (1);
}

int			point_init(t_pt *point, char *row, int i, int j)
{
	if (!point || !row)
		return (0);
	point->x = j;
	point->y = i;
	point->z = ft_atoi(row);
	point->ortho_x = 0;
	point->ortho_y = 0;
	point->float_z = (double)point->z;
	point->iso_x = 0;
	point->iso_y = 0;
	return (1);
}

t_line		*line_init(t_ev *ev, t_pt pt1, t_pt pt2)
{
	t_line *nl;

	if (!(nl = malloc(sizeof(t_line))))
		return (NULL);
	nl->start = &pt1;
	nl->end = &pt2;
	nl->dsum = 0;
	nl->axis = '0';
	nl->slope = 1;
	nl->dx = 0;
	nl->dy = 0;
	nl->z1 = pt1.float_z + (ev->z_min * -1);
	nl->z2 = pt2.float_z + (ev->z_min * -1);
	get_axis(nl, pt1, pt2);
	get_start(ev, nl, pt1, pt2);
	X1 = nl->start->iso_x;
	Y1 = nl->start->iso_y;
	X2 = nl->end->iso_x;
	Y2 = nl->end->iso_y;
	return (nl);
}
