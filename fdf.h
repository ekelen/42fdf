#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 10			// dunno

# define WIDTH 1600
# define HEIGHT 900

# define MLX ev->mlx
# define WIN ev->win
# define MAPH ev->map_height
# define MAPW ev->map_width

# include <stdio.h>				// KILL PRINTF
# include <mlx.h>				// graphics
# include <math.h>				// math
# include <stdlib.h>			// file i/o, malloc
# include <fcntl.h>				// file i/o
# include <unistd.h>			// write
# include "./libft/libft.h"



typedef struct		s_pt
{
	double			x_pt;
	double			y_pt;
	double			z_pt;
}					t_pt;

typedef struct		s_ev
{
	void			*mlx;
	void			*win;

	int				z_max;
	int				z_min;
	int				map_height;
	int				map_width;

	t_pt			**map;
}					t_ev;


int		get_next_line(const int fd, char **line);
int		read_map(char *file);

#endif