#include "fdf.h"

int		melt_color(t_color *color)
{
	color->rbase = 10;
	color->gbase = 50;
	color->bbase = 100;
	color->r_rg = 100;
	color->g_rg = 200;
	color->b_rg = 155;
	return (1);
}