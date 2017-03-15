/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 00:40:05 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 11:54:15 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double		get_g(t_color *color, t_line *nl, double inc, double axe)
{
	double a;
	double zdiff;
	double z1_c;
	double z2_c;

	a = LZR ? color->g_rg / LZR : 0;
	zdiff = LZR ? nl->z2 - nl->z1 : 0;
	z1_c = a ? a * nl->z1 + color->gbase : color->gbase / 10;
	z2_c = a ? a * nl->z2 + color->gbase : color->gbase / 10;
	color->g = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static double		get_r(t_color *color, t_line *nl, double inc, double axe)
{
	double a;
	double zdiff;
	double z1_c;
	double z2_c;

	a = LZR ? color->r_rg / LZR : 0;
	zdiff = LZR ? nl->z2 - nl->z1 : 0;
	z1_c = a ? a * nl->z1 + color->rbase : color->rbase;
	z2_c = a ? a * nl->z2 + color->rbase : color->rbase;
	color->r = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static double		get_b(t_color *color, t_line *nl, double inc, double axe)
{
	double a;
	double zdiff;
	double z1_c;
	double z2_c;

	a = LZR ? color->b_rg / LZR : 0;
	zdiff = LZR ? nl->z2 - nl->z1 : 0;
	z1_c = a ? a * nl->z1 + color->bbase : color->bbase;
	z2_c = a ? a * nl->z2 + color->bbase : color->bbase;
	color->b = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static int			mix_color(t_color *color)
{
	int color_int;

	color_int = 0;
	color_int += ((unsigned char)color->a);
	color_int *= 256;
	color_int += ((unsigned char)color->r);
	color_int *= 256;
	color_int += ((unsigned char)color->g);
	color_int *= 256;
	color_int += ((unsigned char)color->b);
	return (color_int);
}

int					test_color(t_ev *ev, t_line *nl, double inc, double axe)
{
	int		color_int;
	t_color *color;

	color_int = 0;
	LZR = ev->z_range;
	color = (t_color *)malloc(sizeof(t_color));
	color_init(color);
	if (ev->temp)
	{
		shift_temp(ev, color);
		get_b(color, nl, inc, axe);
		get_r(color, nl, inc, axe);
		get_g(color, nl, inc, axe);
		get_a(color, nl, ev);
	}
	color_int = mix_color(color);
	free(color);
	return (color_int);
}
