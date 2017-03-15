/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 13:22:10 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 13:22:12 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		rotate_pts(t_ev *ev, int i, double angle)
{
	double	xo;
	double	yo;
	int		j;

	j = 0;
	xo = IS_X;
	yo = IS_Y;
	while (j < ev->ix)
	{
		xo = IS_X;
		yo = IS_Y;
		IS_X = (cos(angle * DIR) * xo) - (sin(angle * DIR) * yo);
		IS_Y = (sin(angle * DIR) * xo) + (cos(angle * DIR) * yo);
		j++;
	}
	return (1);
}

static int		rotate(t_ev *ev)
{
	int				i;
	static double	angle = .10;

	i = 0;
	get_xy_minmax(ev);
	fdf_offset(ev, -ev->iso_ctr_x, -ev->iso_ctr_y);
	while (i < ev->iy)
	{
		rotate_pts(ev, i, angle);
		i++;
	}
	fdf_offset(ev, ev->iso_ctr_x, ev->iso_ctr_y);
	angle += .10;
	return (1);
}

static int		init_draw(t_ev *ev, int i)
{
	int j;

	j = 0;
	while (j < ev->ix)
	{
		mlx_pixel_put(ev->mlx, ev->win, IS_X, IS_Y, 0x00333333);
		if (j < ev->ix - 1)
			draw(ev, ev->points[i][j], ev->points[i][j + 1]);
		if (i < ev->iy - 1)
			draw(ev, ev->points[i][j], ev->points[i + 1][j]);
		j++;
	}
	return (1);
}

int				render_mlx(t_ev *ev)
{
	int i;
	int j;

	if (!ev)
	{
		ft_putendl_fd(ERR_RENDER, 2);
		return (0);
	}
	j = 0;
	i = 0;
	get_ortho_coords(ev);
	get_new_iso(ev);
	get_offset(ev);
	fdf_offset(ev, ev->offset_x, ev->offset_y);
	if (ev->rotate_opt == 1)
		rotate(ev);
	mlx_clear_window(ev->mlx, ev->win);
	ev->start_true = 0;
	while (i < ev->iy)
	{
		init_draw(ev, i);
		i++;
	}
	return (1);
}

int				launch_mlx(t_ev *ev)
{
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "FDF");
	ev->start_true = 1;
	render_mlx(ev);
	if (!(mlx_key_hook(ev->win, my_key_function, ev)))
		exit(0);
	mlx_loop(ev->mlx);
	return (1);
}
