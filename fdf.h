#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 10			// dunno

# define WIDTH 800
# define HEIGHT 800
# define MARGIN 80

# define MLX ev->mlx
# define WIN ev->win

# include <stdio.h>				// KILL PRINTF
# include <mlx.h>				// graphics
# include <math.h>				// math
# include <stdlib.h>			// file i/o, malloc
# include <fcntl.h>				// file i/o
# include <unistd.h>			// write
# include "./libft/libft.h"



typedef struct		s_pt
{
	double			x;
	double			y;
	double			z;
}					t_pt;

typedef struct		s_ev
{
	void			*mlx;
	void			*win;

	int				z_max;
	int				z_min;
	double				x_len;
	double				y_height;
	int				pt_sum;
	double			ratio;
	double			width;
	double			height;
	int				origin_x;
	int				origin_y;

	int				offset_y;
	int				offset_x;

	int				padding;

	t_pt			**points;
	
}					t_ev;


int		get_next_line(const int fd, char **line);
int		read_map(char *file, t_ev *ev);
int		map_init(char **strmap, t_ev *ev);
int		launch_mlx(t_ev *ev);

#endif
