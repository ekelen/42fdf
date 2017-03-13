#ifndef FDF_H
# define FDF_H

# include <stdio.h>				// KILL PRINTF
# include <mlx.h>				// graphics
# include <math.h>				// math
# include <stdlib.h>			// file i/o, malloc
# include <fcntl.h>				// file i/o
# include <unistd.h>			// write
# include <time.h>
# include "./libft/libft.h"

/*
** Screen macros
*/

# define WIDTH 1000
# define HEIGHT 1000

# define MLX ev->mlx
# define WIN ev->win

/*
** Point macros
*/

# define IS_X (*ev).points[i][j].iso_x
# define IS_Y (*ev).points[i][j].iso_y

# define IS_XMIN ev->xmin
# define IS_XMAX ev->xmax
# define IS_YMIN ev->ymin
# define IS_YMAX ev->ymax

# define OR_X (*ev).points[i][j].ortho_x
# define OR_Y (*ev).points[i][j].ortho_y

/*
** Error messages
*/

# define ERR_EMPTY "Error : Empty map."
# define ERR_JAGGED "Error : Map is not rectangular."
# define ERR_INV "Error : Invalid map file."
# define ERR_LINE "Error : Invalid map file or invalid characters in map."
# define ERR_ALLOC "Error : Could not allocate heap space."
# define ERR_SIZE "Error : Please try a smaller map (< 300 side length)."

/*
** Equation formatting
*/

# define DIR ev->dir
# define LZR nl->zr

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
	double			zr;
}					t_line;

typedef struct		s_ev
{
	t_pt			**points;
	void			*mlx;
	void			*win;

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

	double			iso_ctr_x;
	double			iso_ctr_y;

	double			offset_y;	// how much to move object by in order to keep it all on the screen
	double			offset_x;	// ^^

	double			o_x_off; // need for translation
	double			o_y_off; // need for translation
	double			zoom_factor;
	double			trans_const_x;
	double			trans_const_y;
	double			z_mod;

	double			ortho_scale;
	int				rotate_opt;
	int				dir;

	int				start_true;

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
int			fdf_twist(t_ev *ev);

/*
** Generic helpers
*/

int			get_xy_minmax(t_ev *ev);
int			get_z_minmax(t_ev *ev);
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

#endif
