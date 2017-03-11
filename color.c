#include "fdf.h"

static int	mix_color(t_ev *ev, t_color *color)
{
	(void)ev;
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
	double zr = ev->z_range;
	double a = zr ? 255 / zr : 0;
	double zdiff = zr ? nl->z2 - nl->z1 : 0;


	double z1_c = a ? a * nl->z1 : 0;
	double z2_c = a ? a * nl->z2 : 0;
	printf("c_inc = %.f, z = %.f, zr = %.f, z_rel_color = %.f\n", a, nl->z1, zr, z1_c);


	color = (t_color *)malloc(sizeof(t_color));
	color_init(color);
	color->r = 0;
	color->g = 0;
	color->b = zdiff ? z1_c + (((z2_c - z1_c) * increment) / axe) : z1_c;

	//printf("z1 : %f\n", nl->z1);
	//if (rl && rs && color->b == 0)
	//{
	//printf("nl->dx : %.f\n", nl->dx);	
	//printf("(section * nl->z1) + (increment * z2-z1) : (%.1f * %.1f) + (%f * %.f - %.f)\n", section, nl->z1, increment, nl->z2, nl->z1);
//}
	//printf("Height : %f, Where : %f\n", height, z);
	//printf("color b : %i", color->b);
	//color->a = 200;
	color_int = mix_color(ev, color);
	//printf("Value : %#x (%d)\n", color_int, color_int);
	free(color);
	return (color_int);
}