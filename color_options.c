/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 00:50:45 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 00:51:23 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_a(t_color *color, t_line *nl, t_ev *ev)
{
	if (ev->ix < 2 || ev->iy < 2 || ZR < 2)
		return (0);
	if (Y1 > 0 && ev->iy > 0 && ev->temp == 3)
		color->a = (1000 - fabs(Y1)) / 4;
	else if (Y1 > 0 && ev->iy > 0)
		color->a = (1000 - fabs(Y1)) / 10;
	return (1);
}

int		freeze_color(t_color *color)
{
	color->rbase = 80;
	color->gbase = 100;
	color->bbase = 200;
	color->r_rg = 155;
	color->g_rg = 155;
	color->b_rg = 55;
	return (1);
}

int		melt_color(t_color *color)
{
	color->rbase = 1;
	color->gbase = 50;
	color->bbase = 200;
	color->r_rg = 1;
	color->g_rg = 200;
	color->b_rg = 55;
	return (1);
}

int		combust_color(t_color *color)
{
	color->rbase = 220;
	color->gbase = 50;
	color->bbase = 20;
	color->r_rg = 10;
	color->g_rg = 200;
	color->b_rg = 70;
	return (1);
}

int		evaporate_color(t_color *color)
{
	color->rbase = 75;
	color->gbase = 75;
	color->bbase = 75;
	color->r_rg = 170;
	color->g_rg = 170;
	color->b_rg = 170;
	return (1);
}
