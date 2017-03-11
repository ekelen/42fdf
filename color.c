#include "fdf.h"

static double	get_r(t_color *color, t_line *nl, double inc, double axe)
{
	double a = LZR ? 80 / LZR : 0;
	double zdiff = LZR ? nl->z2 - nl->z1 : 0;
	double z1_c = a ? a * nl->z1 + 55 : 55;
	double z2_c = a ? a * nl->z2 + 55 : 55;
	color->r = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}


static double	get_b(t_color *color, t_line *nl, double inc, double axe)
{
	double a = LZR ? 200 / LZR : 0;
	double zdiff = LZR ? nl->z2 - nl->z1 : 0;
	double z1_c = a ? a * nl->z1 + 55 : 55;
	double z2_c = a ? a * nl->z2 + 55 : 55;
	color->b = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static int	mix_color(t_color *color)
{
	//(void)ev;
	int color_int;
	color_int = 0;
	color_int += ((unsigned char)color->r);
	color_int *= 256;
	color_int += ((unsigned char)color->g);
	color_int *= 256;
	color_int += ((unsigned char)color->b);
	return (color_int);
}

int	test_color(t_ev *ev, t_line *nl, double increment, double axe)
{
	int color_int = 0;
	t_color *color;
	LZR = ev->z_range;
	color = (t_color *)malloc(sizeof(t_color));
	color_init(color);
	color->r = 0;
	color->g = 0;
	get_b(color, nl, increment, axe);
	get_r(color, nl, increment, axe);
	color_int = mix_color(color);
	free(color);
	return (color_int);
}