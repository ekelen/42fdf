#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 10			// dunno

# include <stdio.h>				// KILL PRINTF
# include <mlx.h>				// graphics
# include <math.h>				// math
# include <stdlib.h>			// file i/o, malloc
# include <fcntl.h>				// file i/o
# include <unistd.h>			// write
# include "./libft/libft.h"

int	get_next_line(const int fd, char **line);


#endif