NAME = fdf

SRCS += main.c
SRCS += get_next_line.c
SRCS += launch_mlx.c
SRCS += read_map.c
SRCS += map_init.c
SRCS += obj_init.c
SRCS += pixel_draw.c
SRCS += pixel_draw_helpers.c
SRCS += key_hooks.c
SRCS += hook_mods.c
SRCS += fdf_recalculators.c
SRCS += color.c
SRCS += color_options.c
SRCS += helpers.c

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME)

# To make .o files
$(OBJS): $(SRCS)
	@$(CC) -Wall -Wextra -Werror -c $(SRCS) -I minilibx_macos

# To make executable "fdf", needed for rule make all
# Compiles .o files with lmlx library and required flags
$(NAME): $(OBJS)
	@make -C libft/
	@$(CC) $(OBJS) -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -L libft -lft -o $(NAME)
	@echo "[FDF compiled.]\n"

clean:
	@make -C libft clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

