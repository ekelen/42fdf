NAME = fdf

SRCS += main.c
SRCS += get_next_line.c
SRCS += launch_mlx.c
SRCS += read_map.c
SRCS += map_init.c
SRCS += obj_init.c
SRCS += pixel_draw.c
SRCS += fdf_translate.c

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME)

# debug: CC += -g
# debug: $(NAME)

# To make .o files
$(OBJS): $(SRCS)
	$(CC) -g -Wall -Wextra -Werror -c $(SRCS) -I minilibx_macos

# To make executable "fdf", needed for rule make all
# Compiles .o files with lmlx library and required flags
$(NAME): $(OBJS) 
	$(CC) -g $(OBJS) -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -L libft -lft -o $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

