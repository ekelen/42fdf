#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 10			// dunno

# define WIDTH 1000
# define HEIGHT 1000
//# define MARGIN 50

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

# define KEY_PLUS 69
# define KEY_MINUS 78

# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29


/*
** Key macros
*/

# define MOVE_UP -20
# define MOVE_DOWN 20
# define MOVE_LEFT -20
# define MOVE_RIGHT 20

# define ZOOM_IN 1.33
# define ZOOM_OUT .77

# define HIGHER 3
# define LOWER -3

// # define ROTATE_LEFT 10;
// # define ROTATE_RIGHT -10;







typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

}					t_color;

typedef struct		s_pt
{
	int				x;
	int				y;
	int				z;

	double			ortho_x;
	double			ortho_y;

	double			float_z;

	double			z_times_ratio;
	double			iso_x;
	double			iso_y;

	t_color			*color;
}					t_pt;




typedef struct		s_line
{
	t_pt			*start;
	t_pt			*end;
	double			z1;
	double			z2;
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

	double			xrange;		// object width
	double			yrange;

	double			ix;		// greatest num of points along X axis
	double			iy;		// greatest num of points along Y axis - change to int

	double			origin_x;	// leftmost point
	double			origin_y;	// uppermost point

	double			iso_ctr_x;
	double			iso_ctr_y;

	double			offset_y;	// how much to move object by in order to keep it all on the screen
	double			offset_x;	// ^^

	double			offset_x_add;
	double			offset_y_add;
	double			o_x_off;
	double			o_y_off;
	// double			o_wd;
	// double			o_ht;
	// double			o_xctr;
	// double			o_yctr;
	// double			o_xmax;
	// double			o_ymax;
	// double			o_xmin;
	// double			o_ymin;

	t_pt			**points;

	double			ortho_scale;
	int				rotate_opt;
	int				dir;

}					t_ev;


t_ev		*new_ev(t_ev *ev);
int			get_next_line(const int fd, char **line);
int			read_map(char *file, t_ev *ev);
int			map_init(char **strmap, t_ev *ev);
int			launch_mlx(t_ev *ev);
int			point_init(t_pt *point, char *row, int i, int j);
int			draw(t_ev *ev, t_pt pt1, t_pt pt2);

int			fdf_offset(t_ev *ev, double off_x, double off_y);
int			render_mlx(t_ev *ev);

/*
** Generic helpers
*/
int			get_xy_minmax(t_ev *ev);
int			get_ortho_coords(t_ev *ev);
int			get_new_iso(t_ev *ev);
double		get_center_x(t_ev *ev);
double		get_center_y(t_ev *ev);
int			resize_to_fit(t_ev *ev);
int			fdf_twist(t_ev *ev);
int			color_init(t_color *color);
int			test_color(t_ev *ev, t_line *nl, double increment, double axe);

/*
** Key hooks
*/
int			key_hook_translation(int keycode, t_ev *ev);
int			key_hook_zoom(int keycode, t_ev *ev);
int			key_hook_rotate(int keycode, t_ev *ev);
int			key_hook_height(int keycode, t_ev *ev);
int			key_hook_twist(int keycode, t_ev *ev);

#endif
