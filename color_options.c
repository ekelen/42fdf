#include "fdf.h"

double get_a(t_color *color, t_line *nl, t_ev *ev)
{
	if (ev->ix < 2 || ev->iy < 2 || ZR < 2)
		return (0);
	if (nl->y1 > 0 && ev->iy > 0 && ev->temp == 3)
		color->a = (1000 - fabs(nl->y1)) / 4;
	return (1);
}

int		freeze_color(t_color *color)
{
	color->rbase = 100;
	color->gbase = 100;
	color->bbase = 200;
	color->r_rg = 155;
	color->g_rg = 155;
	color->b_rg = 55;
	return (1);
}

int		melt_color(t_color *color)
{
	color->rbase = 50;
	color->gbase = 100;
	color->bbase = 200;
	color->r_rg = 100;
	color->g_rg = 55;
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
	color->rbase = 100;
	color->gbase = 100;
	color->bbase = 100;
	color->r_rg = 100;
	color->g_rg = 100;
	color->b_rg = 100;
	return (1);
}