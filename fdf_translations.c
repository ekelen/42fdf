/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_translations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 01:41:29 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/13 01:41:37 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_relief(t_ev *ev, double z_up, int incline)
{
	INC_DIR = incline;
	ev->z_mod += z_up * INC_DIR;
	render_mlx(ev);
	return (1);
}

int	fdf_translate(t_ev *ev, double x, double y)
{
	ev->trans_const_x += x;
	ev->trans_const_y += y;
	render_mlx(ev);
	return (1);
}

int	fdf_zoom(t_ev *ev, double x)
{
	ev->zoom_factor *= x;
	render_mlx(ev);
	return (1);
}

int	fdf_offset(t_ev *ev, double off_x, double off_y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			IS_X += off_x;
			IS_Y += off_y;
			j++;
		}
		i++;
	}
	ev->offset_x = 0;
	ev->offset_y = 0;
	return (1);
}
