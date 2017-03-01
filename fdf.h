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
	int				x;
	int				y;
	int				z;

	double			ortho_x;
	double			ortho_y;

	double			iso_x;
	double			iso_y;
}					t_pt;



typedef struct		s_ev
{
	void			*mlx;
	void			*win;

	int				z_max;		// highest given value for Z
	int				z_min;		// lowest given value for Z
	double			x_len;		// greatest num of points along X axis
	double			y_height;	// greatest num of points along Y axis

	int				pt_sum;		// number of points; redundant ?
	double			ratio;		// ratio of width : height

	double			ortho_width;		// width of active map in pixels
	double			ortho_height;		// height of active map in pixels
	double				origin_x;	// leftmost point
	double				origin_y;	// uppermost point

	int				offset_y;	// the largest illustrated Y coordinate
	int				offset_x;	// the largest illustrated X coordinate

	int				padding;	// num of pixels btw points
	int				ortho_scale;
	int				tmp_iso_scale;

	t_pt			***points;
	
}					t_ev;



int		get_next_line(const int fd, char **line);
int		read_map(char *file, t_ev *ev);
int		map_init(char **strmap, t_ev *ev);
int		launch_mlx(t_ev *ev, t_pt **points);
int		point_init(t_pt *point, char *row, int i, int j);
t_pt		find_iso_coord(t_ev *ev, t_pt point, int i, int j);

#endif
