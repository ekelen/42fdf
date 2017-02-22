NAME = fdf

SRCS += main.c
SRCS += get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# To make .o files
$(OBJS): $(SRCS)
	gcc -Wall -Wextra -Werror -c $(SRCS) -I minilibx_macos

# To make executable "fdf", needed for rule make all
# Compiles .o files with lmlx library and required flags
$(NAME): $(OBJS) 
	gcc $(OBJS) -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -L libft -lft -o $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all