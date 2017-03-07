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

/*
**	Key codes
*/

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define MOVE_UP -100
# define MOVE_DOWN 100
# define MOVE_LEFT -100
# define MOVE_RIGHT 100



typedef struct		s_pt
{
	int				x;
	int				y;
	int				z;

	double			ortho_x;
	double			ortho_y;

	double			float_z;

	double			iso_x;
	double			iso_y;
}					t_pt;

typedef struct		s_line
{
	t_pt			*start;
	t_pt			*end;
	char			axis;
	double			dsum;
	double			dx;
	double			dy;
	int				slope;
	double			x1;
	double			x2;
	double			y1;
	double			y2;

}					t_line;




typedef struct		s_ev
{
	void			*mlx;
	void			*win;
	int				sw;
	int				sh;

	int				z_max;		// highest given value for Z
	int				z_min;		// lowest given value for Z
	int				z_range;
	int				z_ratio;

	int				xmax;
	int				ymax;

	int				xmin;
	int				ymin;

	int				xrange;
	int				yrange;

	double			ix;		// greatest num of points along X axis
	double			iy;	// greatest num of points along Y axis

	int				pt_sum;		// number of points; redundant ?

	double			ortho_width;		// width of active map in pixels
	double			ortho_height;		// height of active map in pixels
	int				origin_x;	// leftmost point
	int				origin_y;	// uppermost point

	int				offset_y;	// the largest illustrated Y coordinate
	int				offset_x;	// the largest illustrated X coordinate

	int				padding;	// num of pixels btw points
	double			ortho_scale;
	int				tmp_iso_scale;

	t_pt			***points;
}					t_ev;



int		get_next_line(const int fd, char **line);
int		read_map(char *file, t_ev *ev);
int		map_init(char **strmap, t_ev *ev);
int		launch_mlx(t_ev *ev, t_pt **points);
int		point_init(t_pt *point, char *row, int i, int j);
int		draw(t_ev *ev, t_pt pt1, t_pt pt2);
double	af(double c);
void	key_hook_translation(int keycode, t_ev *ev);

#endif
