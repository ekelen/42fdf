/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:59:36 by rmonnier          #+#    #+#             */
/*   Updated: 2017/03/12 15:25:38 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "fdf.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

# if BUFF_SIZE <= 0
#  error "invalid BUFF_SIZE"
# endif

int							get_next_line(const int fd, char **line);

typedef	struct				s_struct
{
	int						fd;
	char					*str;
	char					*offset;
	struct s_struct			*next;
	struct s_struct			*prev;
}							t_buffer;

#endif
