# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekelen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 18:23:23 by ekelen            #+#    #+#              #
#    Updated: 2017/02/21 20:10:12 by ekelen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------------------------------------------------------
# COLORES |
# ----------------------------------------------------------------------------
RESET=\033[0m
DARK=\033[132m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
MAGENTA=\033[35m
CYAN=\033[36m
WHITE=\033[37m
BOLDBLACK=\033[1m\033[30m
BOLDRED=\033[1m\033[31m
BOLDWHITE=\033[1m\033[37m

NAME = libft.a

CC= gcc

FLAG += -Wall -Wextra -Werror

SRC = 

# **************************************************************************** #
# PART I - MEMORY                                                              #
# **************************************************************************** #
SRC += ft_memset.c
SRC += ft_bzero.c
SRC += ft_memcpy.c
SRC += ft_memccpy.c
SRC += ft_memmove.c
SRC += ft_memchr.c
SRC += ft_memcmp.c

# **************************************************************************** #
# PART I - STRINGS                                                             #
# **************************************************************************** #
SRC += ft_strlen.c
SRC += ft_strdup.c
SRC += ft_strcpy.c
SRC += ft_strncpy.c
SRC += ft_strcat.c
SRC += ft_strncat.c
SRC += ft_strlcat.c
SRC += ft_strchr.c
SRC += ft_strrchr.c
SRC += ft_atoi.c
SRC += ft_strcmp.c
SRC += ft_strncmp.c
SRC += ft_strstr.c
SRC += ft_strnstr.c
SRC += ft_tolower.c
SRC += ft_toupper.c
SRC += ft_isdigit.c
SRC += ft_isalnum.c
SRC += ft_isalpha.c
SRC += ft_isascii.c
SRC += ft_isprint.c


# **************************************************************************** #
# PART II                                                                      #
# **************************************************************************** #
SRC += ft_memalloc.c
SRC += ft_memdel.c
SRC += ft_strnew.c
SRC += ft_strdel.c
SRC += ft_strclr.c
SRC += ft_striter.c
SRC += ft_striteri.c
SRC += ft_strmap.c
SRC += ft_strmapi.c
SRC += ft_strequ.c
SRC += ft_strnequ.c
SRC += ft_strsub.c
SRC += ft_strjoin.c
SRC += ft_strtrim.c
SRC += ft_strsplit.c
SRC += ft_itoa.c
SRC += ft_putendl.c
SRC += ft_putendl_fd.c
SRC += ft_putchar.c
SRC += ft_putstr.c
SRC += ft_putnbr.c
SRC += ft_putnbr_fd.c
SRC += ft_putchar_fd.c
SRC += ft_putstr_fd.c
SRC += ft_strclr.c

# **************************************************************************** #
# PART III                                                                     #
# **************************************************************************** #
SRC += ft_lstnew.c
SRC += ft_lstdelone.c
SRC += ft_lstdel.c
SRC += ft_lstadd.c
SRC += ft_lstiter.c
SRC += ft_lstmap.c


# **************************************************************************** #
# PART IV - CUSTOM                                                             #
# **************************************************************************** #
SRC += ft_extra_abs.c
SRC += ft_extra_isspace.c
SRC += ft_extra_lstprint.c
SRC += ft_extra_putstrnl.c
SRC += ft_extra_max.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n${CYAN}${NAME} done.${RESET}"

%.o : %.c
	@$(CC) $(FLAG) -c -o $@ $<
	@echo -n .

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
                             
