/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 13:54:55 by ekelen            #+#    #+#             */
/*   Updated: 2017/03/15 19:29:06 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		put_usage(void)
{
	ft_putendlcolor_fd("\n\t\t  ___ ___  ___ ", 1, "bold", 1);
	ft_putendlcolor_fd("\t\t | __|   \\| __|", 1, "bold", 1);
	ft_putendlcolor_fd("\t\t | _|| | || _| ", 1, "bold", 1);
	ft_putendlcolor_fd("\t\t |_| |___/|_|  ", 1, "bold", 1);
	ft_putstr_fd("\n\t\tUsage: ", 1);
	ft_putendlcolor_fd("./fdf filename [", 1, "bold", 0);
	ft_putendlcolor_fd("-melt", 1, "lightgreen", 0);
	ft_putchar_fd('|', 1);
	ft_putendlcolor_fd("-freeze", 1, "cyan", 0);
	ft_putchar_fd('|', 1);
	ft_putendlcolor_fd("-combust", 1, "red", 0);
	ft_putchar_fd('|', 1);
	ft_putendlcolor_fd("-evaporate", 1, "grey", 0);
	ft_putendlcolor_fd("] [-map]\n", 1, "bold", 1);
	show_keyhooks();
	return ;
}

static int		check_args(char *s)
{
	int px;

	px = 0;
	if (!(ft_strcmp(s, "-freeze")))
		px = 1;
	else if (!(ft_strcmp(s, "-combust")))
		px = 2;
	else if (!(ft_strcmp(s, "-evaporate")))
		px = 3;
	else if (!(ft_strcmp(s, "-melt")))
		px = 4;
	else if (!(ft_strcmp(s, "-map")))
		px = 5;
	return (px);
}

static int		check_two_args(t_ev *ev, char *s1, char *s2)
{
	int err;
	int s1_res;
	int s2_res;

	s1_res = check_args(s1);
	s2_res = check_args(s2);
	err = 0;
	if (!s1_res || !s2_res || s1_res == s2_res)
		err = 1;
	else if (s1_res != 5 && s2_res != 5)
		err = 1;
	if (!err)
	{
		ev->temp = s1_res != 5 ? s1_res : s2_res;
		ev->map = 1;
	}
	else
	{
		ft_putendlcolor_fd("ERROR : ", 2, "red", 0);
		ft_putendl_fd(ERR_ARG, 2);
		return (0);
	}
	return (1);
}

static int		parse_arg(t_ev *ev, char *s1)
{
	int s1_res;

	s1_res = check_args(s1);
	if (!s1_res)
	{
		ft_putendlcolor_fd("Error : ", 2, "red", 0);
		ft_putendl_fd(ERR_ARG, 2);
		return (0);
	}
	if (s1_res == 5)
	{
		ev->map = 1;
		return (1);
	}
	ev->temp = s1_res;
	return (1);
}

int				main(int ac, char **av)
{
	t_ev	ev;
	char	*file;

	file = av[1];
	new_ev(&ev);
	put_usage();
	if (ac < 2 || ac > 4)
	{
		ft_putendl_fd(ERR_ARG, 2);
		return (0);
	}
	if (ac == 3)
	{
		if (!(parse_arg(&ev, av[2])))
			return (0);
	}
	else if (ac == 4)
	{
		if (!(check_two_args(&ev, av[2], av[3])))
			return (0);
	}
	if (!(read_map(file, &ev)))
		return (0);
	return (0);
}
