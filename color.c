#include "fdf.h"


static double	get_g(t_color *color, t_line *nl, double inc, double axe)
{
	double a = LZR ? color->g_rg / LZR : 0;
	double zdiff = LZR ? nl->z2 - nl->z1 : 0;
	double z1_c = a ? a * nl->z1 + color->gbase : color->gbase / 10;
	double z2_c = a ? a * nl->z2 + color->gbase : color->gbase / 10;
	color->g = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static double	get_r(t_color *color, t_line *nl, double inc, double axe)
{
	double a = LZR ? color->r_rg / LZR : 0;
	double zdiff = LZR ? nl->z2 - nl->z1 : 0;
	double z1_c = a ? a * nl->z1 + color->rbase : color->rbase;
	double z2_c = a ? a * nl->z2 + color->rbase : color->rbase;
	color->r = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static double	get_b(t_color *color, t_line *nl, double inc, double axe)
{
	double a = LZR ? color->b_rg / LZR : 0;
	double zdiff = LZR ? nl->z2 - nl->z1 : 0;
	double z1_c = a ? a * nl->z1 + color->bbase : color->bbase;
	double z2_c = a ? a * nl->z2 + color->bbase : color->bbase;
	color->b = zdiff ? z1_c + (((z2_c - z1_c) * inc) / axe) : z1_c;
	return (1);
}

static int	mix_color(t_color *color)
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

static int	shift_temp(t_ev *ev, t_color *color)
{
	if (ev->temp == 1)
		freeze_color(color);
	else if (ev->temp == 2)
		combust_color(color);
	else if (ev->temp == 3)
		evaporate_color(color);
	return (1);
}

int	test_color(t_ev *ev, t_line *nl, double increment, double axe)
{
	int color_int = 0;
	t_color *color;
	LZR = ev->z_range;
	color = (t_color *)malloc(sizeof(t_color));
	color_init(color);
	if (ev->temp)
	{
		shift_temp(ev, color);
		get_b(color, nl, increment, axe);
		get_r(color, nl, increment, axe);
		get_g(color, nl, increment, axe);
		get_a(color, nl, ev);
	}
	color_int = mix_color(color);
	free(color);
	return (color_int);
}