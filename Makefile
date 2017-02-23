NAME = fdf

SRCS += main.c
SRCS += get_next_line.c
SRCS += read_map.c

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME)

debug: CC += -g

# To make .o files
$(OBJS): $(SRCS)
	$(CC) -Wall -Wextra -Werror -c $(SRCS) -I minilibx_macos

# To make executable "fdf", needed for rule make all
# Compiles .o files with lmlx library and required flags
$(NAME): $(OBJS) 
	$(CC) $(OBJS) -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -L libft -lft -o $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: fclean
	$(NAME)
