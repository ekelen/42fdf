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
# include <time.h>
# include "./libft/libft.h"

/*
**	Key codes
*/

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_PLUS 18
# define KEY_MINUS 19

# define MOVE_UP -10
# define MOVE_DOWN 10
# define MOVE_LEFT -10
# define MOVE_RIGHT 10

# define ZOOM_IN 1.01
# define ZOOM_OUT .99



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
	double			sw;
	double			sh;

	double			z_max;		// highest given value for Z
	double			z_min;		// lowest given value for Z
	double			z_range;
	double			z_ratio;

	double			xmax;		// max illustrated X point
	double			ymax;		// max illustrated Y point

	double			xmin;		// min illustrated X point
	double			ymin;		// min illustrated Y point

	double			xrange;
	double			yrange;

	double			ix;		// greatest num of points along X axis
	double			iy;		// greatest num of points along Y axis - change to int

	double			origin_x;	// leftmost point
	double			origin_y;	// uppermost point

	double			iso_ctr_x;
	double			iso_ctr_y;

	double			offset_y;	// how much to move object by in order to keep it all on the screen
	double			offset_x;	// ^^

	t_pt			**points;

	double			ortho_scale;

}					t_ev;


t_ev	*new_ev(t_ev *ev);
int		get_next_line(const int fd, char **line);
int		read_map(char *file, t_ev *ev);
int		map_init(char **strmap, t_ev *ev);
int		launch_mlx(t_ev *ev);
int		point_init(t_pt *point, char *row, int i, int j);
int		draw(t_ev *ev, t_pt pt1, t_pt pt2);

int		fdf_offset(t_ev *ev, double off_x, double off_y);



int		render_mlx(t_ev *ev);

/*
** Generic helpers
*/
int		get_xy_minmax(t_ev *ev);
int		init_ortho_coords(t_ev *ev, int i, int j);
int		get_ortho_coords_from_scale(t_ev *ev);
int		get_new_iso(t_ev *ev);
int		get_center(t_ev *ev);
int		fdf_center(t_ev *ev);
int		fdf_recenter(t_ev *ev);

/*
** Key hooks
*/
int		key_hook_translation(int keycode, t_ev *ev);
int		key_hook_zoom(int keycode, t_ev *ev);

#endif
